#include <iostream>
#include <algorithm>
#include <random>
#include <array>
#include <numeric>
#include <random>
#include <ctime>

// initialize Card ranks and Card suits
enum class Cardrank
{
  card_1,
  card_2,
  card_3,
  card_4,
  card_5,
  card_6,
  card_7,
  card_8,
  card_9,
  card_10,
  card_king,
  card_ace,
  card_queen,
  card_jack,

  rank_max
};

enum class Cardsuit
{
  diamond,
  club,
  heart,
  spade,
  suit_max,
};

struct card{
  Cardrank rank{};
  Cardsuit suit{};
};
// make an std::array with 52 length and get all the suits and cards on it

using Deck = std::array<card, 52>;

//make a function that initalizes the Deck

Deck initializeDeck(Deck deck){
  int index{0};

  // now we are going to for loop through the hole array and initalize it with suits and ranks
  for (int suit{0}; suit < (static_cast<int>(Cardsuit::suit_max)); ++suit){
    for (int rank{0}; rank < (static_cast<int>(Cardrank::rank_max)); ++rank)
    {
      // because rank is an int we have to convert it to an rank value
      deck[index].rank = static_cast<Cardrank>(rank);
      deck[index].suit = static_cast<Cardsuit>(suit);
      index++;
    }
  }

  return deck;
}

// shuffle the array

//make a function that gets the array and shuffles it

void shuffle(Deck& deck){
  std::mt19937 mt{static_cast<std::mt19937::result_type>(std::time(nullptr))};

  std::shuffle(deck.begin(), deck.end(), mt);

}


void printCard(card card){
   switch (card.suit)
   {
   case Cardsuit::diamond: std::cout << "D"; break;
   case Cardsuit::heart: std::cout << "H"; break;
   case Cardsuit::club: std::cout << "C"; break;
   case Cardsuit::spade:  std::cout << "S"; break;
   }

   switch (card.rank)
   {
   case Cardrank::card_1: std::cout << 1; break;
   case Cardrank::card_2: std::cout << 2; break;
   case Cardrank::card_3: std::cout << 3; break;
   case Cardrank::card_4: std::cout << 4; break;
   case Cardrank::card_5: std::cout << 5; break;
   case Cardrank::card_6: std::cout << 6; break;
   case Cardrank::card_7: std::cout << 7; break;
   case Cardrank::card_8: std::cout << 8; break;
   case Cardrank::card_9: std::cout << 9; break;
   case Cardrank::card_10: std::cout << 10; break;
   case Cardrank::card_king: std::cout << 'K'; break;
   case Cardrank::card_jack: std::cout << 'J'; break;
   case Cardrank::card_queen: std::cout << 'Q'; break;
   case Cardrank::card_ace: std::cout << 'A'; break;
  }

  std::cout << "  ";
}

void printDeck(Deck& d){
  for(auto elements : d){
    printCard(elements);
  }
}

// get a random card from the array

auto getAnRandomCard(Deck d)
{

  std::random_device rd{};

 // seed
  std::seed_seq seed{
      rd(), rd(), rd(), rd(), rd()
  };

  std::uniform_int_distribution<> uni{0, 52};

  std::mt19937 mt{seed};

  return d[uni(mt)];
}

card dealerCard(const Deck Dealerdeck){
  auto randomCard{getAnRandomCard(Dealerdeck)};
  std::cout << "Dealer has got an card!\n";
  return randomCard;
}

card playerCard(const Deck Playerdeck){
  auto randomCard{getAnRandomCard(Playerdeck)};
  std::cout << "You have got an: ";
  printCard(randomCard);
  std::cout << '\n';
  return randomCard;
}

bool userHitStand(){
  bool stand = false;
  while (true)
  {
    
    std::cout << "\nHit(H) or Stand(S): ";
    char input{};
    std::cin >> input;

    switch (input)
    {
    case 'S':
      stand = true;
      return stand;
    case 'H':
      return stand;
    default:
      std::cout << "PLEASE ENTER AN VAILD INPUT\n";
      break;
    }
  }

  return stand;
}

int checkCards(card& card){

  switch (card.rank)
  {
  case Cardrank::card_1: return 1;
  case Cardrank::card_2: return 2;
  case Cardrank::card_3: return 3;
  case Cardrank::card_4: return 4;
  case Cardrank::card_5: return 5;
  case Cardrank::card_6: return 6;
  case Cardrank::card_7: return 7;
  case Cardrank::card_8: return 8;
  case Cardrank::card_9: return 9;
  case Cardrank::card_10: return 10;
  case Cardrank::card_king:
  case Cardrank::card_queen:
  case Cardrank::card_jack:
    return 10;
  case Cardrank::card_ace: return 11;

  default:
    std::cerr << "UNKNOW ERRROR HAS OCURRED!";
    return 0;
  }
}

void giveCard(const Deck deck){

  int sumPlayer{0};
  int sumDealer{0};
  int totalsumplayer{0};
  int totalsumdealer{0};

  card newPlayer(playerCard(deck));
  card newDealer(dealerCard(deck));

    card newestPlayer(playerCard(deck));
    totalsumplayer = checkCards(newPlayer) + checkCards(newestPlayer);

    int theTotalOfDealer{0};

    int count{1};
    while (true)
    {
    if (!userHitStand())
    {

      card player(playerCard(deck));
      card dealer(dealerCard(deck));
      if(checkCards(player) >= 21){
        std::cout << "Busted sorry you loose!";
        return;
      }
      else if (checkCards(dealer) >= 21){
        std::cout << "Dealer busted you win!";
        return;
      }

      if((checkCards(newPlayer) + checkCards(player)) >= 21){
        std::cout << "Busted sorry you loose!";
        return;
      }

      sumPlayer += (checkCards(player) + totalsumplayer);

      sumDealer += (checkCards(dealer) + checkCards(newDealer));
      
      if(sumDealer > 17){
      if(sumPlayer == sumDealer){
        std::cout << "Its a Tie!";
        return;
      }
      else if (sumPlayer > sumDealer){
        std::cout << "Its a Win!";
        return;
      }
      else if (sumPlayer < sumDealer){
        std::cout << "You loose!";
        return;
      }
    }

      theTotalOfDealer += checkCards(dealer);
      count++;
      
    }else{
      break;
    }
  }

  int totalOfDealerCardsToPlayer{0};
  for (int i{0}; i <= count; i++)
  {
    card Dealer(dealerCard(deck));
    totalOfDealerCardsToPlayer += checkCards(newDealer) + theTotalOfDealer;
  }

  // code if user stands goes here!
  if (checkCards(newPlayer) >= 21){
    std::cout << "Busted sorry you loose!";
    return;
  }
  if (totalOfDealerCardsToPlayer >= 21)
  {
    std::cout << "Dealer busted you win!";
    return;
  }
    
  
    if (checkCards(newPlayer) == totalOfDealerCardsToPlayer)
    {
      std::cout << "Its a Tie!";
    }
    else if (checkCards(newPlayer) > totalOfDealerCardsToPlayer)
    {
      std::cout << "Its a Win!";
    }
    else if (checkCards(newPlayer) < totalOfDealerCardsToPlayer){
      std::cout << "You loose!";
    }
}

int main()
{
  Deck d1{};
  auto deck(initializeDeck(d1));
  shuffle(deck);

  giveCard(deck);

  return 0;
}