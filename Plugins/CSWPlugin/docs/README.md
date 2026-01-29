# CSWPlugin

CSWPlugin is an Unreal Engine plugin that bridges CSW/GizmoSDK scene streaming into Unreal.
It initializes the CSW scene manager, receives command buffers, and builds Unreal components
from Gizmo3D scene graph data.

## Purpose
- Stream large CSW scenes (Gizmo3D) into Unreal.
- Provide a UE component (UCSWScene) that can be placed in a level/actor.
- Handle coordinate and resource translation between GizmoSDK and Unreal.

## Layered stack
1. GizmoSDK (GizmoBase + Gizmo3D) - core types, IO, threading, and scene graph.
2. cswSceneManager - command/buffer layer between Gizmo3D and clients.
3. CSWPlugin - UE glue, adapters, factories, and resource management.
4. Unreal Engine - final rendering and interaction.

## Key plugin parts
- `UEGlue/cswUEGlue` - init/shutdown and log bridge Gizmo <-> UE.
- `cswUESceneManager` - adapter that routes build/destroy callbacks into UE factories.
- `UCSWScene` - component that receives buffers and builds/updates the scene.
- `cswFactory` + `Builders/Factories` - create UE components per Gizmo node type.
- `cswResourceManager` - shared materials/textures.

## Related documentation
- GizmoSDK: `C:\Source\GizmoSDK\docs\howto`
- cswSceneManager: `C:\Source\CSW_Intern\source\Presentation\Streaming\cswSceneManager\README.md`
- cswSceneManager design: `C:\Source\CSW_Intern\source\Presentation\Streaming\cswSceneManager\design.md`
