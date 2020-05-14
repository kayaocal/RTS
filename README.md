# RTS2

**Engine : Unreal Engine 4.24.3**


## Project Layout

* **Content\Maps:** Unreal Engine Maps(Levels) are stored in this folder
* **Content\Data:** DataTable or other data specific files are stored in this folder
* **Content\UI:** UI widgets and other UI specific files are stored here

## Coding

This project uses Unreal's coding conventions system. [LINK](https://docs.unrealengine.com/en-US/Programming/Development/CodingStandard/index.html)  

### Code Folder Layout

* **Source\RTS2\Prerequisites.h:** This module stores general common data types, enums, macros, class definitions etc.. 
* **Source\RTS2\Data:** Data related classes such as derived classes from *FTableRowBase* will be here. 
* **Source\RTS2\Game:** Game Logic related classes. Excluding Actors. 

## Data Structure

* **Content\Data\Unit\UnitNecessity:** This data table stores unit prices or any other necessities specific to Unit type and Nation.. 
* **Content\Data\Unit\UnitConstruction:** This data table stores unit materials or meshes specific to Unit type and Nation and Age..

## Starting Game Multiplayer
On Windows Powershell run the code below. Each code runs one client.
"**[ENGINE_DIR]**\\Engine\\Binaries\\Win64\\UE4Editor.exe" "**[PROJECT_DIRECTORY]**\\RTS\\RTS2.uproject"  -game -log