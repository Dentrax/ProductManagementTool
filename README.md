<h1 align="center">ProductManagementTool Public Source Repository</h1>

**Software Engineering Final Project - Advanced Product tracking automation system**

[What It Is](#what-it-is)

[How To Use](#how-to-use)

[Build & Run](#build-run)

[Requirements](#requirements)

[Dependencies](#dependencies)

[About](#about)  

[Collaborators](#collaborators)  

[Branches](#branches) 

[Copyright & Licensing](#copyright--licensing)  

[Contributing](#contributing)  

[Contact](#contact)

## What It Is

**ProductManagementTool with Qt 5**

ProductManagementTool program for C++ language is an easy and best way to learn how automation systems interact with the database and works in practice.

**Uses : Please see [Requirements](#requirements) and [Dependencies](#dependencies)**

**ProductManagementTool**

---

**Who is the target audience?**

---

* Anyone who wants to do project with Qt

* Students wishing to do their projects using Qt

* Those who need the Automation Program for their homework

* `Warning:` This project assumes you have some Intermediate-Level C++ knowledge, and `does not teach C++ itself.`

* `Warning:` This project are not a `How to create your own automation tool` or `How to design automation tool systems` and will not teach `Automation tooling techniques`.

**Uses : Please see [Requirements](#requirements) before use**

# Screenshots - UML Diagrams

- All UMLs Made with **[StarUML](http://staruml.io)**

- **[Click here](https://github.com/Dentrax/ProductManagementTool/blob/master/diagrams)** for see the all other UML diagrams.

## Program

![Preview Thumbnail](https://raw.githubusercontent.com/Dentrax/ProductManagementTool/master/diagrams/uml/diagram_uml_program.png)

## Database

![Preview Thumbnail](https://raw.githubusercontent.com/Dentrax/ProductManagementTool/master/diagrams/uml/diagram_uml_database.png)

## Activity

![Preview Thumbnail](https://raw.githubusercontent.com/Dentrax/ProductManagementTool/master/diagrams/activity/diagram_activity_general.png)

## Collabration

![Preview Thumbnail](https://raw.githubusercontent.com/Dentrax/ProductManagementTool/master/diagrams/collabration/diagram_collaboration_general.png)

## Use Case

![Preview Thumbnail](https://raw.githubusercontent.com/Dentrax/ProductManagementTool/master/diagrams/usecase/diagram_usecase_general.png)

## Sequence

Login

![Preview Thumbnail](https://raw.githubusercontent.com/Dentrax/ProductManagementTool/master/diagrams/sequence/diagram_sequence_login.png)

- **[Click here](https://github.com/Dentrax/ProductManagementTool/blob/master/diagrams/sequence)** for see the other Squence diagrams.

## Statechart

Login

![Preview Thumbnail](https://raw.githubusercontent.com/Dentrax/ProductManagementTool/master/diagrams/statechart/diagram_statechart_login.png)

- **[Click here](https://github.com/Dentrax/ProductManagementTool/blob/master/diagrams/statechart)** for see the other Statechart diagrams.

# Screenshots - Program GUI

![Preview Thumbnail](https://raw.githubusercontent.com/Dentrax/ProductManagementTool/master/screenshots/ss_panel_login.png)

![Preview Thumbnail](https://raw.githubusercontent.com/Dentrax/ProductManagementTool/master/screenshots/ss_panel_register.png)

![Preview Thumbnail](https://raw.githubusercontent.com/Dentrax/ProductManagementTool/master/screenshots/ss_panel_product-edit.png)

![Preview Thumbnail](https://raw.githubusercontent.com/Dentrax/ProductManagementTool/master/screenshots/ss_panel_main-list.png)

![Preview Thumbnail](https://raw.githubusercontent.com/Dentrax/ProductManagementTool/master/screenshots/ss_panel_main-search.png)

## Features

* Account system with Login/Register features

* Lists the Product fetched from database

* Lists the Product that have been searched from Search panel

* Ability to Add product

* Ability to Update product (exclude ID and Barcode)

* Ability to Delete product

* Advanced search options (by Name, by Date, by Quantity, by Price)

* Product filter

* Safe inputs from Textboxes (bug-free inputs)

* Real-time Product list refreshing if any operate handled

## TO-DO List

* User authority level (Permission system)

* Sales system

* Invoice & Receipt system for sold products

* Product should be Refundable after sold

## Known Issues

* Window Fixed Size feature not working on Linux.

## How To Use

1) git clone https://github.com/dentrax/ProductManagementTool

2) Import **[ProductManagementTool.sql](https://github.com/Dentrax/ProductManagementTool/blob/master/sql/ProductManagementTool.sql)** file to the database

3) Re-configure your database informations in **[dbcontroller.cpp](https://github.com/Dentrax/ProductManagementTool/blob/master/src/dbcontroller.cpp)**'s `SetupDB()` function.

4) [Build and Run!](#build-run)

## Build & Run

`qmake && make && ./ProductManagementTool`

## Requirements

* You should be familiar with Qt applications
* You should be familiar with C++ family
* You will need Qt base environment that can be compiled without any problems.
* You will need a computer on which you have the rights to install obligatory dependencies given below

## Dependencies

* MySQL (or related) Database Service
* Qt Creator is fine (not mandatory)
* Qt Base Modules And Frameworks
* A C++ Compiler (Windows -> MinGW or Visual C++, Linux -> GCC is fine)

## About

ProductManagementTool was created to serve three purposes:

**ProductManagementTool is an automation tool that controls some Product operations using with Database**

1. To act as a guide to learn Qt with enhanced and rich content using `C++`.

2. To act as a guide to exemplary and educational purpose.

3. To create your own Qt application.

## Collaborators

**Project Manager** - Furkan Türkal (GitHub: **[dentrax](https://github.com/dentrax)**)

## Branches

We publish source for the **[ProductManagementTool]** in single rolling branch:

The **[master branch](https://github.com/dentrax/ProductManagementTool/tree/master)** is extensively tested by our QA team and makes a great starting point for learning the algorithms. Also tracks [live changes](https://github.com/dentrax/ProductManagementTool/commits/master) by our team. 

## Copyright & Licensing

The base project code is copyrighted by Furkan 'Dentrax' Türkal and is covered by single licence.

All program code (i.e. .h, .cpp, .ui) is licensed under GNU v3 License unless otherwise specified. Please see the **[LICENSE.md](https://github.com/Dentrax/ProductManagementTool/blob/master/LICENSE)** file for more information.

**References**

While this repository is being prepared, it may have been quoted from some sources. (i.e Official Wiki & Documentations)
If there is an unspecified source, please contact me.

## Contributing

Please check the [CONTRIBUTING.md](CONTRIBUTING.md) file for contribution instructions and naming guidelines.

## Contact

ProductManagementTool was created by Furkan 'Dentrax' Türkal

 * <https://www.furkanturkal.com>
 
You can contact by URL:
    **[CONTACT](https://github.com/dentrax)**

<kbd>Best Regards</kbd>
