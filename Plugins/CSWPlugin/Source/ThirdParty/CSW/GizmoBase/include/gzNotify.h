//*****************************************************************************
//
// Copyright (C) SAAB AB
//
// All rights, including the copyright, to the computer program(s)
// herein belong to SAAB AB. The program(s) may be used and/or
// copied only with the written permission of SAAB AB, or in
// accordance with the terms and conditions stipulated in the
// agreement/contract under which the program(s) have been
// supplied.
//
//
// Information Class:	COMPANY UNCLASSIFIED
// Defence Secrecy:		NOT CLASSIFIED
// Export Control:		NOT EXPORT CONTROLLED
//
//
// File			: gzNotify.h
// Module		: gzBase
// Description	: Class definition of gzNotify utilities
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.224
//		
//
//			
// NOTE:	GizmoBase is a platform abstraction utility layer for C++. It contains 
//			design patterns and C++ solutions for the advanced programmer.
//
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990517	Created file 	
//
//******************************************************************************
#ifndef __GZ_NOTIFY_H__
#define __GZ_NOTIFY_H__

/*!	\file 
	\brief Notification message and handler

The Gizmo3D toolkit uses model-view architecture. The Notification messages and the manager of these messages
are thread safe and priority based in Gizmo3D.
*/


#include "gzBase.h"
#include "gzMutex.h"
#include "gzTime.h"
#include "gzExceptions.h"

// --------------------- Subscriptions ---------------------------------
// Observer notifier pattern. One master and many subscribing slaves

//! Possible notification events as results of subscription changes etc.
enum gzNotifyState
{
	GZ_NOTIFY_ADD_SUBSCRIBER,
	GZ_NOTIFY_CANCEL_ADD_SUBSCRIBER,
	GZ_NOTIFY_MULTIPLE_ADD_SUBSCRIBER,
	GZ_NOTIFY_REMOVE_SUBSCRIBER,
	GZ_NOTIFY_MASTER_TERMINATE,
	GZ_NOTIFY_SLAVE_TERMINATE,
};

template <class SLAVE> class gzPendSub : public gzReference
{
public:
	
	gzPendSub()
	{
	}
		
	virtual ~gzPendSub()
	{
	}
	
	virtual	gzBool	useDeepCopy() 
	{ 
		return FALSE; 
	}
		
	SLAVE *				subscriber;
	gzUInt64			senderClass;
	gzUInt32			pendingID;
};

template <class DATA> class gzPendData : public gzReference
{
public:
	
	gzPendData()
	{
	}
		
	virtual ~gzPendData()
	{
	}
	
	virtual	gzBool	useDeepCopy() 
	{ 
		return FALSE; 
	}	// Default behaviour is to share


		
	DATA			data;
	gzUInt64		senderClass;
	gzDouble		notifyTime;
	gzDouble		timeOut;
};


//******************************************************************************
// Class	: gzNotifyMaster
//									
// Purpose  : Template that implements the Notifier Master in a O/N pattern
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	031012	Created 
//									
//******************************************************************************
template <class MASTER , class SLAVE , class DATA=gzRefPointer<gzReference> > class gzNotifyMaster 
{
public:

	gzNotifyMaster()
	{
		m_pendingID=0;
		m_pendingAddSubs.reuseLinks(TRUE);
		m_pendingRemSubs.reuseLinks(TRUE);
		m_activeSubs.reuseLinks(TRUE);
		m_pendingData.reuseLinks(TRUE);
		m_activeData.reuseLinks(TRUE);
		m_triggerOnNotifyData=TRUE;
		m_inTriggerNotification=FALSE;
	}

	gzNotifyMaster(const gzNotifyMaster<MASTER,SLAVE,DATA> &/*copy*/)
	{
		m_pendingID=0;
		m_pendingAddSubs.reuseLinks(TRUE);
		m_pendingRemSubs.reuseLinks(TRUE);
		m_activeSubs.reuseLinks(TRUE);
		m_pendingData.reuseLinks(TRUE);
		m_activeData.reuseLinks(TRUE);
		m_triggerOnNotifyData=TRUE;
		m_inTriggerNotification=FALSE;
	}

	virtual ~gzNotifyMaster()
	{
		m_activeSubsLocker.waitLock();

		if(m_activeSubs.entries())
		{		
			gzListIterator<gzPendSub<SLAVE> > iterator(m_activeSubs);
		
			gzPendSub<SLAVE> *sub;

			while((sub=iterator()))
			{
				sub->subscriber->m_subscriptionLocker.waitLock();
				sub->subscriber->m_pendingSubscriptions.remove((MASTER *)this);
				sub->subscriber->onNotifyStatus((MASTER *)this,sub->subscriber,GZ_NOTIFY_MASTER_TERMINATE);
				sub->subscriber->m_subscriptionLocker.unLock();
			}
		}
		
		m_activeSubsLocker.unLock();

		m_pendingSubsLocker.waitLock();

		if(m_pendingAddSubs.entries())
		{		
			gzListIterator<gzPendSub<SLAVE> > iterator(m_pendingAddSubs);
		
			gzPendSub<SLAVE> *sub;

			while((sub=iterator()))
			{
				sub->subscriber->m_subscriptionLocker.waitLock();
				sub->subscriber->m_pendingSubscriptions.remove((MASTER *)this);
				sub->subscriber->onNotifyStatus((MASTER *)this,sub->subscriber,GZ_NOTIFY_MASTER_TERMINATE);
				sub->subscriber->m_subscriptionLocker.unLock();
			}
		}

		if(m_pendingRemSubs.entries())
		{		
			gzListIterator<gzPendSub<SLAVE> > iterator(m_pendingRemSubs);
		
			gzPendSub<SLAVE> *sub;

			while((sub=iterator()))
			{
				sub->subscriber->m_subscriptionLocker.waitLock();
				sub->subscriber->m_pendingSubscriptions.remove((MASTER *)this);
				sub->subscriber->onNotifyStatus((MASTER *)this,sub->subscriber,GZ_NOTIFY_MASTER_TERMINATE);
				sub->subscriber->m_subscriptionLocker.unLock();
			}
		}
		
		m_pendingSubsLocker.unLock();

	}

	gzVoid addSubscriber( SLAVE *subscriber , gzUInt64 senderClass=0)
	{
		if(subscriber)
		{
			gzPendSub<SLAVE> *pend=new gzPendSub<SLAVE>;

			pend->subscriber=subscriber;
			pend->senderClass=senderClass;
			pend->pendingID=m_pendingID++;

			m_pendingSubsLocker.waitLock();
			m_pendingAddSubs.insert(pend);
			m_pendingSubsLocker.unLock();

			subscriber->m_subscriptionLocker.waitLock();
			subscriber->m_pendingSubscriptions.insert((MASTER *)this);
			subscriber->m_subscriptionLocker.unLock();
		}
	}

	gzVoid removeSubscriber( SLAVE *subscriber)
	{
		if(subscriber)
		{
			gzPendSub<SLAVE> *pend=new gzPendSub<SLAVE>;

			pend->subscriber=subscriber;
			pend->senderClass=0;
			pend->pendingID=m_pendingID++;

			m_pendingSubsLocker.waitLock();
			m_pendingRemSubs.insert(pend);
			m_pendingSubsLocker.unLock();

			subscriber->m_subscriptionLocker.waitLock();
			subscriber->m_pendingSubscriptions.insert((MASTER *)this);
			subscriber->m_subscriptionLocker.unLock();
		}
	}

	gzVoid notifyData(const DATA &data , gzUInt64 senderClass=0 , const gzDouble &timeOut=GZ_DOUBLE_ZERO, const gzDouble &notifyTime=GZ_DOUBLE_ZERO,const gzUInt32 priority=0 ,gzBool immediateTrigger=FALSE)
	{
		gzPendData<DATA> *pend=new gzPendData<DATA>;
		
		pend->data=data;
		pend->senderClass=senderClass;

		if(timeOut)
			pend->timeOut=gzTime::systemSeconds()+timeOut;
		else
			pend->timeOut=DBL_MAX;

		pend->notifyTime=notifyTime;

		gzBool trigger;

		m_pendingDataLocker.waitLock();
		m_pendingData.post_insert(pend,-(gzDouble)priority);
		trigger=m_triggerOnNotifyData|immediateTrigger;
		m_pendingDataLocker.unLock();

		if(trigger)
			triggerNotifications();

	}

	gzBool triggerNotifications()
	{
		gzBool result=triggerSubscriptionChanges();

		m_activeSubsLocker.waitLock();

		if(!m_inTriggerNotification && movePendingToActiveData())
		{
			m_inTriggerNotification=TRUE;

			if(m_activeData.entries())
			{
				result=TRUE;

				gzDouble now=gzTime::systemSeconds();

				gzListIterator<gzPendData<DATA> > iterator(m_activeData);
				gzPendData<DATA> *pend;

				while((pend=iterator()))
				{
					if(pend->timeOut>now)
					{
						if(pend->notifyTime<=now)
						{
							if(m_activeSubs.entries())
							{
								gzListIterator<gzPendSub<SLAVE> > iterator2(m_activeSubs);
								gzPendSub<SLAVE> *subs;

								while((subs=iterator2()))
								{
									if( (!subs->senderClass) || (subs->senderClass==pend->senderClass))
										subs->subscriber->onNotify((MASTER *)this,pend->data,pend->senderClass);

								}
							}
							iterator.remove();
						}
						// else leave the pending data
					}
					else
					{
						iterator.remove();
					}
				}
			}

			m_inTriggerNotification=FALSE;
		}

		m_activeSubsLocker.unLock();

		return result;
	}

	gzUInt32 getPendingCount()
	{
		GZ_BODYGUARD(m_pendingDataLocker);

		return m_pendingData.entries();
	}

	gzBool movePendingToActiveData()
	{
		//GZ_ASSERT(!m_activeData.entries());

		m_pendingDataLocker.waitLock();

		m_activeData += m_pendingData;
		m_pendingData.clear();

		m_pendingDataLocker.unLock();

		return GZ_BOOL(m_activeData.entries());
	}

	gzBool triggerSubscriptionChanges()
	{
		m_activeSubsLocker.waitLock();
		m_pendingSubsLocker.waitLock();

		gzBool result=FALSE;

		// check for removals

		if(m_pendingRemSubs.entries())
		{
			result=TRUE;

			gzListIterator<gzPendSub<SLAVE> > iterator(m_pendingRemSubs);
			gzPendSub<SLAVE> *remove;

			while((remove=iterator()))
			{
				// Check if cancel any add

				if(m_pendingAddSubs.entries())
				{
					gzListIterator<gzPendSub<SLAVE> > iterator2(m_pendingAddSubs);
					gzPendSub<SLAVE> *add;

					while((add=iterator2()))
					{
						if(add->subscriber==remove->subscriber)
						{
							if(add->pendingID<remove->pendingID)
							{
								remove->subscriber->m_subscriptionLocker.waitLock();
	
								remove->subscriber->m_pendingSubscriptions.remove((MASTER *)this);
							
								remove->subscriber->onNotifyStatus((MASTER *)this,remove->subscriber,GZ_NOTIFY_REMOVE_SUBSCRIBER);
		
								remove->subscriber->m_subscriptionLocker.unLock();
							
								onNotifyStatus(remove->subscriber,GZ_NOTIFY_CANCEL_ADD_SUBSCRIBER);

								iterator2.remove();
							}
						}
					}
				}

				// Remove from subscriptions

				if(m_activeSubs.entries())
				{
					gzListIterator<gzPendSub<SLAVE> > iterator2(m_activeSubs);
					gzPendSub<SLAVE> *sub;

					while((sub=iterator2()))
					{
						if(sub->subscriber==remove->subscriber)
						{
							sub->subscriber->m_subscriptionLocker.waitLock();
	
							sub->subscriber->m_pendingSubscriptions.remove((MASTER *)this);
							
							sub->subscriber->onNotifyStatus((MASTER *)this,sub->subscriber,GZ_NOTIFY_REMOVE_SUBSCRIBER);
		
							sub->subscriber->m_subscriptionLocker.unLock();
							
							onNotifyStatus(sub->subscriber,GZ_NOTIFY_REMOVE_SUBSCRIBER);
							
							iterator2.remove();
						}
					}
				}

				// remove pending change

				remove->subscriber->m_subscriptionLocker.waitLock();
				remove->subscriber->m_pendingSubscriptions.remove((MASTER *)this);
				remove->subscriber->m_subscriptionLocker.unLock();
						
			}
			m_pendingRemSubs.clear();
		}

		
		// check for adds

		if(m_pendingAddSubs.entries())
		{
			gzListIterator<gzPendSub<SLAVE> > iterator2(m_pendingAddSubs);
			gzPendSub<SLAVE> *add;

			gzBool	addItem;

			result=TRUE;

			while((add=iterator2()))
			{
				// Check if cancel any add

				addItem=TRUE;

				if(m_activeSubs.entries())
				{
					gzListIterator<gzPendSub<SLAVE> > iterator3(m_activeSubs);
					gzPendSub<SLAVE> *sub;

					while((sub=iterator3()))
					{
						if(add->subscriber==sub->subscriber)
						{
							if(!sub->senderClass)
								addItem=FALSE;
							else if(!add->senderClass)
								iterator3.remove();
							else if(add->senderClass==sub->senderClass)
								addItem=FALSE;
						}
					}
				}

				if(addItem)
				{
					if(m_pendingRemSubs.entries())
					{
						gzListIterator<gzPendSub<SLAVE> > iterator3(m_pendingRemSubs);
						gzPendSub<SLAVE> *sub;

						while((sub=iterator3()))
						{
							if(add->subscriber==sub->subscriber)
							{
								if(!sub->senderClass)
									addItem=FALSE;
								else if(add->senderClass==sub->senderClass)
									addItem=FALSE;
							}
						}
					}
				}

				if(addItem)
				{
					m_activeSubs.insert(add);
					
					add->subscriber->m_subscriptionLocker.waitLock();
					
					add->subscriber->onNotifyStatus((MASTER *)this,add->subscriber,GZ_NOTIFY_ADD_SUBSCRIBER);
					
					add->subscriber->m_subscriptionLocker.unLock();
					
					onNotifyStatus(add->subscriber,GZ_NOTIFY_ADD_SUBSCRIBER);
				}
				else
				{
					add->subscriber->m_subscriptionLocker.waitLock();
	
					add->subscriber->m_pendingSubscriptions.remove((MASTER *)this);
							
					add->subscriber->onNotifyStatus((MASTER *)this,add->subscriber,GZ_NOTIFY_MULTIPLE_ADD_SUBSCRIBER);
		
					add->subscriber->m_subscriptionLocker.unLock();
				}
					

		
			}

			m_pendingAddSubs.clear();
		}

		m_pendingID=0;	

		m_pendingSubsLocker.unLock();
		m_activeSubsLocker.unLock();

		return result;
	}

	gzVoid triggerOnNotifyData(gzBool on)
	{
		GZ_BODYGUARD(m_pendingDataLocker);

		m_triggerOnNotifyData=on;
	}

    //! We must provide this callback for status
	virtual gzVoid onNotifyStatus(SLAVE * /*slave*/ ,gzNotifyState /*state*/ ){};


private:

	gzMutex							m_pendingSubsLocker;
	gzRefList<gzPendSub<SLAVE> >	m_pendingAddSubs;
	gzRefList<gzPendSub<SLAVE> >	m_pendingRemSubs;

	gzRefList<gzPendSub<SLAVE> >	m_activeSubs;
	gzMutex							m_activeSubsLocker;

	gzUInt32						m_pendingID;

	gzMutex							m_pendingDataLocker;
	gzRefList<gzPendData<DATA> >	m_pendingData;
	gzRefList<gzPendData<DATA> >	m_activeData;

	gzBool							m_triggerOnNotifyData;
	gzBool							m_inTriggerNotification;
};

//******************************************************************************
// Class	: gzNotifySlave
//									
// Purpose  : Template that implements the Observer Slave in a O/N pattern
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	031012	Created 
//									
//******************************************************************************
template <class MASTER , class SLAVE , class DATA=gzRefPointer<gzReference> > class gzNotifySlave 
{
public:

	gzNotifySlave()
	{
	}

	gzNotifySlave(const gzNotifySlave<MASTER,SLAVE,DATA> &/*copy*/)
	{
	}

	gzVoid removeSubscriptions()
	{
		m_subscriptionLocker.waitLock();

		if(m_pendingSubscriptions.entries())
		{
			gzList<MASTER>	pendingSubscriptions=m_pendingSubscriptions;

			m_subscriptionLocker.unLock();
		
			gzListIterator<MASTER> iterator(pendingSubscriptions);
		
			MASTER *pending;

			while((pending=iterator()))
			{
				pending->removeSubscriber((SLAVE *)this);
				pending->triggerSubscriptionChanges();
				pending->onNotifyStatus((SLAVE *)this,GZ_NOTIFY_SLAVE_TERMINATE);
			}
		}
		else
			m_subscriptionLocker.unLock();
	}

	virtual ~gzNotifySlave()
	{
		removeSubscriptions();
	}

    //! We must provide this callback for notify
	virtual gzVoid onNotify(MASTER *master,DATA &data,gzUInt64 senderClass)=0;

	//! We must provide this callback for status
    virtual gzVoid onNotifyStatus(MASTER * /*master*/ ,SLAVE * /*slave*/ , gzNotifyState /*state*/){};

protected:

	friend class gzNotifyMaster<MASTER,SLAVE,DATA>;

	gzList<MASTER>	m_pendingSubscriptions;

	gzMutex			m_subscriptionLocker;
};

//******************************************************************************
// Class	: gzNotifyMessage
//									
// Purpose  : Default notification message
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	031012	Created 
//									
//******************************************************************************
class gzNotifyMessage : public gzReference
{
public:

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_BASE_EXPORT);	// RTTI

	GZ_BASE_EXPORT gzNotifyMessage(const gzString &command, const gzDouble& duration, gzTypeInterface *sender, gzReference *data, const gzDouble& number);

	GZ_BASE_EXPORT virtual ~gzNotifyMessage(){};

	GZ_BASE_EXPORT gzString &			getCommand();
	GZ_BASE_EXPORT gzTypeInterface *	getSender();
	GZ_BASE_EXPORT gzReference *		getData();
	GZ_BASE_EXPORT gzTime &				getTime();
	GZ_BASE_EXPORT gzTime &				getLastValidTime();
	GZ_BASE_EXPORT const gzDouble&		getNumber();

	//-------------- clone interface ---------------
	GZ_BASE_EXPORT virtual gzReference *clone()  const override;
		
private:

	gzString						m_command;
	gzTypeInterface					*m_sender;
	gzRefPointer<gzReference>		m_data;
	gzTime							m_time;
	gzTime							m_valid;
	gzDouble						m_number;
};

class gzNotifyManager; // Forward decl of manager

class gzNotifyInterface : public gzNotifySlave<gzNotifyManager,gzNotifyInterface,gzRefPointer<gzNotifyMessage> > 
{
public:
    GZ_BASE_EXPORT virtual gzVoid onNotifyStatus(gzNotifyManager * /*master*/ ,gzNotifyInterface * /*slave*/ , gzNotifyState /*state*/){};
    
};
		
class gzNotifyManager : public gzNotifyMaster<gzNotifyManager,gzNotifyInterface,gzRefPointer<gzNotifyMessage> > 
{
public:
	GZ_BASE_EXPORT	gzNotifyManager();
	GZ_BASE_EXPORT	virtual ~gzNotifyManager();

	GZ_BASE_EXPORT gzVoid notify(const gzString &command , const gzUInt32 priority =0 , const gzDouble & duration=0.0 , gzTypeInterface *sender=nullptr, gzReference *data=nullptr , gzUInt32 counter=0,gzBool immediateTrigger=FALSE);
	GZ_BASE_EXPORT gzVoid notify_gzString(const gzString &command , const gzString &data, gzTypeInterface *sender=nullptr,gzBool immediateTrigger=FALSE);
	
	// ------------------ generic notifier ----------------------

	GZ_BASE_EXPORT static gzNotifyManager &getManager();
    
    GZ_BASE_EXPORT virtual gzVoid onNotifyStatus(gzNotifyInterface * /*slave*/ ,gzNotifyState /*state*/ ){};
};


#endif
