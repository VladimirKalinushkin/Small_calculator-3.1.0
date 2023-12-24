
#pragma once
#include "Small_calculator.h"


int main() {

    welcome_words(); 

    try {

        main_menu(Main_settings, Stream);

    }
    catch(exception){

        cerr << "Произошла неизвестная ошибка!";
        system("pause");

    }
     
    return 0; 
	
}
 