# CSWPlugin

CSWPlugin ar ett Unreal Engine-plugin som kopplar CSW/GizmoSDK streaming till Unreal. Pluginet
initierar cswSceneManager, tar emot command buffers och skapar/uppdaterar Unreal-objekt
utifran data i Gizmo3D scenegraph.

## Syfte
- Stromma stora CSW-scener (Gizmo3D) in i Unreal.
- Erbjuda en UE-komponent (UCSWScene) som kan placeras i en level/actor.
- Hantera koordinat- och resurskonvertering mellan GizmoSDK och Unreal.

## Lager (stack)
1. GizmoSDK (GizmoBase + Gizmo3D) - grundlager med scenegraph, IO och threading.
2. cswSceneManager - buffert/kommando-lager mellan Gizmo3D scenegraph och klienter.
3. CSWPlugin - UE glue, adapters och factories som bygger Unreal-komponenter.
4. Unreal Engine - slutlig presentation och interaktion.

## Viktiga delar i pluginet
- `UEGlue/cswUEGlue` - init/shutdown och logg-brygga Gizmo <-> UE.
- `cswUESceneManager` - adapter som kopplar cswSceneManager till UE-factories.
- `UCSWScene` - komponent som tar emot buffers och bygger/scenar uppdateringar.
- `cswFactory` + `Builders/Factories` - skapar UE-komponenter per Gizmo-nodtyp.
- `cswResourceManager` - delade resurser (material/mesh etc).

## Mer dokumentation
- GizmoSDK: `C:\Source\GizmoSDK\docs\howto`
- cswSceneManager: `C:\Source\CSW_Intern\source\Presentation\Streaming\cswSceneManager\README.md`
- cswSceneManager design: `C:\Source\CSW_Intern\source\Presentation\Streaming\cswSceneManager\design.md`
