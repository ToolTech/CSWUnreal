# Design - CSWPlugin

## Kontext
CSWPlugin ligger ovanfor cswSceneManager och anvander GizmoSDK (framfor allt Gizmo3D)
indirekt via CSW-lagret. Pluginet exponerar en Unreal-komponent som kan streama och
visualisera CSW-scener i en UE-level.

## Lager och ansvar
- GizmoSDK (GizmoBase + Gizmo3D): grundlager med scenegraph, IO, threading och loader-stod.
- cswSceneManager: buffert och kommando-flode mellan Gizmo3D scenegraph och klienter.
- CSWPlugin: UE glue, adapters, factories och resurs-hantering.
- Unreal Engine: slutlig rendering, aktorer/komponenter och editor/runtime-stod.

## Flode av data och kommandon
1. cswSceneManager tar emot kommandon (t.ex. SetMapUrls, RefreshScene) och traverserar
   Gizmo3D scenegraph.
2. Under traversal genereras ut-buffers (Generic, Error, Frame, New, Delete).
3. `UCSWScene` tar emot buffers via `onCommand`, lagrar dem och processar dem per tick.
4. Noder byggs eller tas bort genom factory-lagret, vilket skapar Unreal-komponenter.

## Bygg av scen till Unreal
- `cswUESceneManager` override: `preBuildReference` och `preDestroyReference`.
- Dessa routas till `cswFactory`, som valjer factory baserat pa `gzType`.
- Resultatet ar `UCSWSceneComponent`-instanser som kopplas till UE-hierarkin.

## Init/shutdown och logg
- `cswInitializeUnrealGlue()` startar logg-bryggan mellan `gzMessage` och `UE_LOG`,
  laddar konfiguration och initierar `cswSceneManager::initializeSceneSystem()`.
- `cswUnInitializeUnrealGlue()` stanger ned och frigor resurser.

## Threading och prestanda
- `cswSceneManager` ar en `gzThread` och producerar buffers asynkront.
- Buffers bearbetas i UE-komponenten i korta steg for att undvika langa lockar.
- Buffer-typer hanteras separat for att styra bygghastighet och frame-latens.

## Designprinciper
- Tydlig lagerindelning: GizmoSDK -> cswSceneManager -> CSWPlugin -> Unreal.
- Minimera direkt beroende mot Gizmo3D i UE-kod; ga via CSW-lagret.
- Kort livslangd pa locks och snabb hantering av inkommande buffers.
