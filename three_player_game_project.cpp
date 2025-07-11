#include <iostream>
using namespace std;
/* You are tasked with implementing a simple number guessing game in c++ involving Guesser, Three Players, an Umpire. 
 The game operates as follow :                 
 Guesser : This entity will guess a number x.
 Players : Each of the players will guess a number.
 Umpire : This entity will collect the guesses from Guesser and the Players and determine the Players, (if any) have guessed the same number as the Guesser.
 
 EX: 
 x->4 number guessed by the Gusser
 p1->2, p2->4, p3->6
 p1 : lost the game
 p2 : won the game
 p3 : lost the game */
 
 class Guesser{
     public: 
     int guessedNum;
     int takeGuesserInput(){
         int g;
         cout<<"Give the number for the Guesser : ";
         cin>>g;
         guessedNum = g;
         return guessedNum;
     }
 };
 
 class Player{
     public: 
     int playerNum;
     int takePlayerInput(){
         int p;
         cin>>p;
         playerNum = p;
         return playerNum;
     }
 };
 
 class Umpire{
     public: 
     int gnum, p1num, p2num, p3num;
     void getNumGuesser(){
         Guesser G;
         gnum = G.takeGuesserInput();
     }
     void getNumPlayer(){
         Player P1;
         cout<<"Give the number guessed by the player 1 : ";
         p1num = P1.takePlayerInput();
         Player P2;
         cout<<"Give the number guessed by the player 2 : ";
         p2num = P2.takePlayerInput();
         Player P3;
         cout<<"Give the number guessed by the player 3 : ";
         p3num = P3.takePlayerInput();
     }
     void PrintResult(){
         if(p1num==gnum && p2num==gnum && p3num==gnum){
             cout<<"Congratulations !!!"<<endl;
             cout<<"All the payers have won the game!!"<<endl;
         }
         else if(p1num!=gnum && p2num!=gnum && p3num!=gnum){
             cout<<"oops !!! "<<endl;
             cout<<"All the payers have lost the game!!"<<endl;
         }
         else if(p1num==gnum && p2num==gnum){
             cout<<"Player 1 and Player 2 have won the game."<<endl;
         }
         else if(p1num==gnum && p3num==gnum){
             cout<<"Player 1 and Player 3 have won the game."<<endl;
         }
         else if(p2num==gnum && p3num==gnum){
             cout<<"Player 2 and Player 3 have won the game."<<endl;
         }
         else if(p1num==gnum){
             cout<<"Player 1 won the game."<<endl;
         }
         else if(p2num==gnum){
             cout<<"Player 2 won the game."<<endl;
         }
         else if(p3num==gnum){
             cout<<"Player 3 won the game."<<endl;
         }
        return;
     }
 };


int main() {
    
    cout<<"------------ Let's start the game ------------"<<endl;
    Umpire u;
    u.getNumGuesser();
    u.getNumPlayer();
    u.PrintResult();
    
    cout<<"------------------ End Game ------------------"<<endl;                
    
    return 0;
}