# CSW - Common Synthetic World  

A project aiming to create a fast stream implementation in Unreal Engine.

## Setup

1. Install UE 5.5
2. Checkout files from repo (incl LFS) and generate a solution from CSW.uproject by rightclick and select *Generate Visual Studio Files* from unreal menu
3. Drop a CSWDevTest instance into a scene
4. Enter a map url to a .gzd map in the *Map Urls* property (there is a map provided in the download under */maps*)
5. Enable **GZ_INSTRUMENT_CODE** in the CSWPlugin.Build.cs file if you want to measure performance
6. The map will load in Editor mode but performance is measured between play and stop
7. You will get output from the log when you filter on sender **CSW**

## CSWPlugin overview

CSWPlugin exposes a `UCSWScene` component that connects Unreal to the CSW scene manager (GizmoSDK).
Key responsibilities:
- Map streaming via `MapUrls` and the CSW command pipeline.
- Scene graph creation/destruction on the game thread (buffered from the manager).
- Coordinate conversion between geodetic, Gizmo, and UE space.
- Ground clamp request/response helpers (polling, event, and async BP node).

Common entry points:
- `UCSWScene::RequestGroundClampPosition(...)` + `TryGetGroundClampResponse(...)` (polling).
- `UCSWScene::OnGroundClampResponse` (event/callback).
- `GroundClampAsync` (Blueprint async node: `UCSWGroundClampAsyncAction`).

## CSWDev test

`ACSWDevTest` is a lightweight test actor (C++ + Blueprint friendly). It includes:
- Geodetic conversion test (forward + reverse).
- Ground clamp test (polling) and an async example helper.

### DevTest via Blueprint

You can create a lightweight DevTest in Blueprint by inheriting from `ACSWDevTest`:

1. Create a Blueprint class based on **ACSWDevTest**.
2. Place the Blueprint actor in your level.
3. Set **bRunGeoTest**, **TestLatitude**, **TestLongitude**, **TestAltitude** in Details.
4. Implement the Blueprint events:
   - **OnGeoTestComplete(WorldPos, LatitudeDeg, LongitudeDeg, AltitudeMeters)**
   - **OnGeoTestFailed()** (optional)

If you need coordinate conversion in Blueprint, call:
- `GeodeticToWorldBP(...)`
- `WorldToGeodeticBP(...)`

These wrappers use the current loaded map coordinate system and route through GizmoSDK -> UE transforms.

### Ground clamp in DevTest (Blueprint)

Polling example (built in):
- Set **bRunGroundClampTest = true** and the ground clamp fields.
- Implement:
  - **OnGroundClampTestComplete(Result)**
  - **OnGroundClampTestFailed()**

Async example (recommended for BP):
- Call **RunGroundClampAsyncExample(TimeoutSeconds)**.
- Bind **OnSuccess / OnFail** on the returned async action node.

### Ground clamp in C++

Minimal polling pattern:
```
const int32 RequestId = Scene->RequestGroundClampPosition(Lat, Lon, Height, WaitForData);
FCSWGroundClampResult Result;
if (Scene->TryGetGroundClampResponse(RequestId, Result))
{
    // Use Result.WorldPosition / WorldNormal / WorldUp / Altitude
}
```

Requests are asynchronous; do not block the game thread.

## Contacts

If you have questions you can email [Anders Modén](mailto:anders.moden@saabgroup.com) or send support question to [GizmoSDK Support](mailto:gizmosdk@saabgroup.com?subject=CSW&body=Help!)

## Work

This demo is based on a streaming technique developed at Saab. It is compatible with other stream formats but has a number of specific features.

You can see a demo here [Video](https://gizmosdk.blob.core.windows.net/video/Streaming%20Maps/AUV%20Buildings%20and%20Trees.mp4)

And Work on some BUGS in UE 5.5 [UE BUG Video](https://youtu.be/JAmdk1Qlzxc)
