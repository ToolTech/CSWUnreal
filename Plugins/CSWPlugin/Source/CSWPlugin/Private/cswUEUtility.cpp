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
// File			: cswUEUtility.cpp
// Module		: CSW StreamingMap Unreal
// Description	: Utilities for UE from GizmoSDK
// Author		: Anders Modén		
// Product		: CSW 1.1.1
//		
//
//			
// NOTE:	CSW (Common Synthetic World) is a simulation and presentation
//			framework for large scale digital twins on multiple platforms
//
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	241107	Created file 					(1.1.1)
//
//******************************************************************************
#include "UEGlue/cswUEUtility.h"

#undef UpdateResource

UTexture2D* cswUETexture2DFromImage(gzImage* image,gzUInt32 /*layer*/)
{
	if (!image)
		return nullptr;

	UTexture2D* newTexture(nullptr);

	TArrayView<uint8> InImageData((uint8 *)image->getArray().getAddress(), image->getArray().getSize());
	
	switch (image->getImageType())
	{
		case GZ_IMAGE_TYPE_RGB_8_DXT1:
			newTexture = UTexture2D::CreateTransient(image->getWidth(), image->getHeight(), PF_DXT1 , (const char *)image->getName(),InImageData);
			break;
	}

	if (!newTexture)
		return nullptr;

	if(image->hasSubImage())	// MipMaps
	{
		for (gzUInt32 i = 0; i < image->getNumberOfSubImages(); i++)
		{
			gzImage* subImage = image->getSubImage(i);

			if (subImage)
			{
				gzUInt32 BytesForImage = subImage->getArray().getSize();

				if (BytesForImage)
				{
					FTexture2DMipMap* Mip = new FTexture2DMipMap(subImage->getWidth(), subImage->getHeight(), 1);

					newTexture->GetPlatformData()->Mips.Add(Mip);

					InImageData= TArrayView<uint8>((uint8*)subImage->getArray().getAddress(), BytesForImage);

					Mip->BulkData.Lock(LOCK_READ_WRITE);
			
					void* DestImageData = Mip->BulkData.Realloc(BytesForImage);

					FMemory::Memcpy(DestImageData, InImageData.GetData(), BytesForImage);

					Mip->BulkData.Unlock();
				}
			}
		}
	}
		
	newTexture->UpdateResource();

	return newTexture;
}

void cswScreenMessage(const gzString& message, const FColor& color)
{
	GZ_SYNCRONIZED;

	static gzInt32 line = 0;

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(line, 10.f, color, message.getWideString());

	line = (line + 1) % 40;
}