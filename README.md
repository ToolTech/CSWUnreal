# CSW - Common Synthetic World  

A project aiming to create a fast stream implementation in Unreal Engine.

## Setup

1. Install UE 5.5
1. Checkout files from repo and generate a solution from CSW.uproject by rightclick and select *Generate Visual Strudio Files* from unreal menu
1. Drop a CSWDevTest instance into a scene
1. Enter a map url to a gzd map in the *Map Urls* property (there is a map provided in the download under */maps*)
1. Enable **GZ_INSTRUMENT_CODE** in the CSWPlugin.Build.cs file if you want to measure performance

## Contacts

If you have questions you can email [Anders Modén](mailto:anders.moden@saabgroup.com) or send support question to [GizmoSDK Support](mailto:gizmosdk@saabgroup.com?subject=CSW&body=Help!)

## Work

This demo is based on a streaming technique developed at Saab. It is compatible with other stream formats but has a number of specific features.

You can see a demo here [Video](https://gizmosdk.blob.core.windows.net/video/Streaming%20Maps/AUV%20Buildings%20and%20Trees.mp4)