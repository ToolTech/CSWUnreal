# Design - CSWPlugin

## Context
CSWPlugin sits above cswSceneManager and uses GizmoSDK (primarily Gizmo3D) indirectly via
the CSW layer. The plugin exposes an Unreal component that can stream and visualize CSW
scenes inside a UE level.

## Layers and responsibilities
- GizmoSDK (GizmoBase + Gizmo3D): scene graph, IO, threading, loaders, math.
- cswSceneManager: buffer and command flow between Gizmo3D and clients.
- CSWPlugin: UE glue, adapters, factories, and resource management.
- Unreal Engine: final rendering, actors/components, editor/runtime integration.

## Command and data flow
1. cswSceneManager consumes incoming commands (e.g. SetMapUrls, RefreshScene) and traverses
   the Gizmo3D scene graph.
2. Traversal produces outgoing buffers (Generic, Error, Frame, New, Delete).
3. `UCSWScene` receives buffers via `onCommand`, queues them, and processes them on tick.
4. New/delete buffers are routed through the factory layer to create/destroy UE components.

## Scene build pipeline
- `cswUESceneManager` overrides `preBuildReference` / `preDestroyReference`.
- These calls are routed to `cswFactory`, which selects a factory by `gzType`.
- Factories build `UCSWSceneComponent` instances and attach them into the UE hierarchy.

## Texture and material path (current)
- `cswResourceManager` maps a Gizmo state to a UE material instance.
- The base material is `/CSWPlugin/Materials/cswBaseMaterial`.
- A texture is created from the Gizmo image and bound to the `baseTexture` parameter.

## Threading and performance
- cswSceneManager runs as a `gzThread` and produces buffers asynchronously.
- `UCSWScene` processes a bounded number of frames and primitives per tick.
- Buffer types are handled separately to control frame latency and build throughput.

## LOD policy (current)
- Gizmo decides which nodes are active based on observer distance.
- UE mesh components currently force LOD0 via `ForcedLodModel = 1` in `UCSWGeometry`.
  This can be revisited if UE-side LOD should be allowed for additional FPS gains.

## Design principles
- Keep layer boundaries clear: GizmoSDK -> cswSceneManager -> CSWPlugin -> Unreal.
- Prefer fast, bounded processing on the game thread.
- Avoid long locks and keep buffer handling short.
