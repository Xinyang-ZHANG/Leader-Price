cmake_minimum_required(VERSION 3.9)
project(Leader_Price)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.12.3/lib/cmake")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON) # if you have any .ui files
set(CMAKE_AUTORCC ON) # if you have any .qrc files

find_package(Qt5Widgets REQUIRED)

qt5_generate_moc(main.cpp main.moc)
qt5_add_resources(RESOURCES mainres.qrc)
add_executable(Leader_Price main.cpp Purchase_DP.h Houseware.h Clothing.h HouseWare.cpp Clothing.cpp Food.h Food.cpp Drink.h Drink.cpp Purchase_DP.h Purchase_DP.cpp Merchandise.h Merchandise.cpp MyException.h MyException.cpp Cashier.h Cashier.cpp ListCashier.h ListCashier.cpp Manager.h Manager.cpp Account.cpp Account.h MyButton.h MyButton.cpp Interface.h Interface.cpp LabelTimer.h LabelTimer.cpp)

target_link_libraries(Leader_Price Qt5::Core Qt5::Widgets Qt5::Gui)