#pragma once
#include <SFML/Graphics.hpp>

struct Theme {
    sf::Color background;
    sf::Color cellHidden;
    sf::Color cellRevealed;
    sf::Color flag;
    sf::Color mine;
    sf::Color textColors[9];
};

const Theme DarkTheme = {
    sf::Color(30, 30, 30),      // background
    sf::Color(60, 60, 60),      // hidden 
    sf::Color(180, 180, 180),   // revealed 
    sf::Color(50, 150, 250),    // flag 
    sf::Color(250, 50, 50),     // mine
    /*
        text colors 0->8
    */
    { sf::Color::Transparent, sf::Color::Blue, sf::Color::Green, sf::Color::Red,
      sf::Color(128, 0, 128), sf::Color(128, 0, 0), sf::Color(64, 224, 208),
      sf::Color::Black, sf::Color::White }
};

const Theme ClassicTheme = {
    sf::Color(192, 192, 192),
    sf::Color(220, 220, 220),
    sf::Color(160, 160, 160),
    sf::Color::Red,          
    sf::Color::Black,        
    { sf::Color::Transparent, sf::Color::Blue, sf::Color::Green, sf::Color::Red,
      sf::Color(128, 0, 128), sf::Color(128, 0, 0), sf::Color(64, 224, 208),
      sf::Color::Black, sf::Color::White }
};

/*
    i actually used gemini to generate the themes below, but they came out pretty nice in my opinion
*/

const Theme Pastel = {
    sf::Color(255, 240, 245),
    sf::Color(255, 182, 193),
    sf::Color(240, 240, 240),
    sf::Color(255, 105, 180),
    sf::Color(147, 112, 219),
    { sf::Color::Transparent, sf::Color(70, 130, 180), sf::Color(60, 179, 113), sf::Color(218, 112, 214),
      sf::Color(255, 127, 80), sf::Color::Black, sf::Color::Black, sf::Color::Black, sf::Color::Black }
};

const Theme Lava = {
    sf::Color(20, 0, 0),        
    sf::Color(100, 20, 0),      
    sf::Color(50, 10, 0),       
    sf::Color(255, 200, 0),     
    sf::Color(255, 255, 255),   
    { sf::Color::Transparent, sf::Color(255, 165, 0), sf::Color(255, 69, 0), sf::Color(255, 0, 0),
      sf::Color(139, 0, 0), sf::Color::Yellow, sf::Color::White, sf::Color::White, sf::Color::White }
};

const Theme Noir = {
    sf::Color(0, 0, 0),         
    sf::Color(40, 40, 40),      
    sf::Color(255, 255, 255),   
    sf::Color(255, 0, 0),       
    sf::Color(100, 100, 100),   
    { sf::Color::Transparent, sf::Color(50, 50, 50), sf::Color(80, 80, 80), sf::Color(120, 120, 120),
      sf::Color(160, 160, 160), sf::Color::Black, sf::Color::Black, sf::Color::Black, sf::Color::Black }
};

const Theme Midas = {
    sf::Color(20, 20, 5),        
    sf::Color(212, 175, 55),     
    sf::Color(255, 223, 0),      
    sf::Color(255, 255, 255),    
    sf::Color(50, 50, 50),       
    { sf::Color::Transparent, sf::Color(139, 69, 19), sf::Color(101, 67, 33), sf::Color(60, 30, 0),
      sf::Color::Black, sf::Color::Black, sf::Color::Black, sf::Color::Black, sf::Color::Black }
};

const Theme Abyss = {
    sf::Color(0, 5, 15),         
    sf::Color(0, 40, 80),        
    sf::Color(0, 20, 40),        
    sf::Color(0, 255, 127),      
    sf::Color(255, 140, 0),      
    { sf::Color::Transparent, sf::Color(135, 206, 250), sf::Color(70, 130, 180), sf::Color(30, 144, 255),
      sf::Color(0, 0, 139), sf::Color::Cyan, sf::Color::White, sf::Color::White, sf::Color::White }
};

const Theme Emerald = {
    sf::Color(1, 50, 32),        
    sf::Color(34, 139, 34),      
    sf::Color(144, 238, 144),    
    sf::Color(255, 215, 0),      
    sf::Color(139, 69, 19),      
    { sf::Color::Transparent, sf::Color(0, 100, 0), sf::Color(107, 142, 35), sf::Color(85, 107, 47),
      sf::Color(128, 0, 0), sf::Color::Black, sf::Color::Black, sf::Color::Black, sf::Color::Black }
};

const Theme Coffee = {
    sf::Color(44, 24, 16),    
    sf::Color(111, 78, 55),   
    sf::Color(236, 224, 209), 
    sf::Color(193, 154, 107), 
    sf::Color(60, 30, 20),    
    { sf::Color::Transparent, sf::Color(101, 67, 33), sf::Color(139, 69, 19), sf::Color(160, 82, 45),
      sf::Color(210, 105, 30), sf::Color(90, 50, 30), sf::Color::Black, sf::Color::Black, sf::Color::Black }
};