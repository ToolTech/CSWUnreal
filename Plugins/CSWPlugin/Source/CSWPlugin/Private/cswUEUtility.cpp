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
// Product		: CSW 1.1.2
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

//#if WITH_EDITOR
//#include "TextureCompiler.h"
//#endif

#undef UpdateResource

UTexture2D* cswUETexture2DFromImage(gzImage* image)
{
	if (!image)
		return nullptr;

	gzImagePtr _image;

	UTexture2D* newTexture(nullptr);

	EPixelFormat pixelFormat(PF_Unknown);

	// Check compatible pixel format

	switch (image->getImageType())
	{
		case GZ_IMAGE_TYPE_BW_8:
			pixelFormat = PF_G8;
			break;

		case GZ_IMAGE_TYPE_BW_16:
			pixelFormat = PF_G16;
			break;

		case GZ_IMAGE_TYPE_RGBA_8:
			pixelFormat = PF_R8G8B8A8;
			break;


		case GZ_IMAGE_TYPE_RGB_8_DXT1:
		case GZ_IMAGE_TYPE_RGBA_8_DXT1:
			pixelFormat = PF_DXT1;
			break;

		case GZ_IMAGE_TYPE_RGBA_8_DXT3:
			pixelFormat = PF_DXT3;
			break;

		case GZ_IMAGE_TYPE_RGBA_8_DXT5:
			pixelFormat = PF_DXT5;
			break;

		default:
			{
				switch (image->getFormat())
				{
					case GZ_IMAGE_FORMAT_LUMINANCE:

						switch ((gzUInt32)image->getBytesPerComponent())
						{
							case 1:
								pixelFormat = PF_G8;
								break;

							case 2:
								pixelFormat = PF_G16;
								break;

						}
						break;

					case GZ_IMAGE_FORMAT_RGBA:

						switch ((gzUInt32)image->getBytesPerComponent())
						{
							case 1:
								pixelFormat = PF_R8G8B8A8;
								break;

							case 2:
								pixelFormat = PF_R16G16B16A16_UINT;
								break;

						}
						break;

					case GZ_IMAGE_FORMAT_COMPRESSED_RGB_S3TC_DXT1:
					case GZ_IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT1:
						pixelFormat = PF_DXT1;
						break;

					case GZ_IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT3:
						pixelFormat = PF_DXT3;
						break;

					case GZ_IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT5:
						pixelFormat = PF_DXT5;
						break;

				}
			}
			break;
	}

	if (pixelFormat == PF_Unknown)
	{
		GZMESSAGE(GZ_MESSAGE_WARNING, "No conversion found for pixel format %d", image->getFormat());

		_image = gzImage::createImage(GZ_IMAGE_TYPE_RGBA_8);

		_image = image->create(_image);

		image = _image.get();

		pixelFormat = PF_R8G8B8A8;
	}

	// Create the texure
	// newTexture = UTexture2D::CreateTransient(image->getWidth(), image->getHeight(), pixelFormat, (const char*)image->getName());
	newTexture = NewObject<UTexture2D>(GetTransientPackage(), MakeUniqueObjectName(GetTransientPackage(), UTexture2D::StaticClass(), "CSWTexture"), RF_Transient | RF_DuplicateTransient | RF_TextExportTransient);


	// Initialize the texture properties
	newTexture->SetPlatformData(new FTexturePlatformData());
	newTexture->GetPlatformData()->SizeX = image->getWidth();
	newTexture->GetPlatformData()->SizeY = image->getHeight();
	newTexture->GetPlatformData()->PixelFormat = pixelFormat;
	newTexture->NeverStream = true;

	if (!newTexture)
		return nullptr;

	// Dont do this in constructor as we add mode mips lateron and this is not thread safe


	gzUInt32 MipSize = image->getNumberOfSubImages() + 1;

	// ---------- MIP 0 ----------------------------

	newTexture->GetPlatformData()->Mips.Reserve(MipSize); // Ok to reserve, but we need to allocate
	FTexture2DMipMap* Mip = new FTexture2DMipMap(image->getWidth(), image->getHeight());

	Mip->BulkData.Lock(LOCK_READ_WRITE);
	gzUInt32 BytesForImage = image->getArray().getSize();
	void* DestImageData = Mip->BulkData.Realloc(BytesForImage);
	FMemory::Memcpy(DestImageData, (uint8*)image->getArray().getAddress(), BytesForImage);
	Mip->BulkData.Unlock();

	newTexture->GetPlatformData()->Mips.Add(Mip);


	// ---------- SUB MIPS -------------------------------

	// Now onto possible sub images

	if (image->hasSubImage())	// MipMaps
	{
		for (gzUInt32 i = 0; i < image->getNumberOfSubImages(); i++)
		{
			gzImage* subImage = image->getSubImage(i);

			if (subImage)
			{
				if (subImage->getWidth() == 0)
					GZBREAK;

				if (subImage->getHeight() == 0)
					GZBREAK;

				BytesForImage = subImage->getArray().getSize();

				if (BytesForImage)
				{
					Mip = new FTexture2DMipMap(subImage->getWidth(), subImage->getHeight(), 1);

					Mip->BulkData.Lock(LOCK_READ_WRITE);
					DestImageData = Mip->BulkData.Realloc(BytesForImage);
					FMemory::Memcpy(DestImageData, (uint8*)subImage->getArray().getAddress(), BytesForImage);
					Mip->BulkData.Unlock();

					newTexture->GetPlatformData()->Mips.Add(Mip);
				}
			}
		}
	}

	// Now we release it to texture compiler

	newTexture->UpdateResource();

	//FTextureCompilingManager::Get().FinishCompilation({ newTexture });

	//newTexture->WaitForPendingInitOrStreaming();

	return newTexture;
}

void cswScreenMessage(const gzString& message, const gzInt32& line, const FColor& color)
{
	GZ_SYNCRONIZED;

	static gzInt32 currentLine = 0;

	if (line >= 0)
		currentLine = line;

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(currentLine, 10.f, color, message.getWideString());

	currentLine = (currentLine + 1) % 40;
}
