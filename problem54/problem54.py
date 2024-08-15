#Author: Bruce Hart <bruce.hart@gmail.com>

#The file, poker.txt, contains one-thousand random hands dealt to two players. Each line of the file contains ten cards
#(separated by a single space): the first five are Player 1's cards and the last five are Player 2's cards. You can
#assume that all hands are valid (no invalid characters or repeated cards), each player's hand is in no specific order,
#and in each hand there is a clear winner.
#
#How many hands does Player 1 win?

import time

class Card:
    CLUB = 1
    HEART = 2
    DIAMOND = 3
    SPADE = 4

    ACE = 1
    TWO = 2
    THREE = 3
    FOUR = 4
    FIVE = 5
    SIX = 6
    SEVEN = 7
    EIGHT = 8
    NINE = 9
    TEN = 10
    JACK = 11
    QUEEN = 12
    KING = 13
    ACE_HIGH = 14

    NO_CARD = -1

    __VAL_STRING  = 'A23456789TJQK'
    __SUIT_STRING = 'CHDS'

    suit = 0
    cardvalue = 0

    def __init__(self, handvalue='XX'):

        if self.__VAL_STRING.count(handvalue[0]):
            self.cardvalue = self.__VAL_STRING.index(handvalue[0])+1
        elif self.__VAL_STRING.count(handvalue[1]):
            self.cardvalue = self.__VAL_STRING.index(handvalue[1])+1
        else:
            self.cardvalue = self.NO_CARD

        if self.__SUIT_STRING.count(handvalue[1]):
            self.suit = self.__SUIT_STRING.index(handvalue[1])+1
        elif self.__SUIT_STRING.count(handvalue[0]):
            self.suit = self.__SUIT_STRING.index(handvalue[0])+1
        else:
            self.suit = self.NO_CARD

    def __str__(self):
        if self.cardvalue > 0 and self.suit > 0:
            return "{0}{1}".format(self.__VAL_STRING[self.cardvalue-1],self.__SUIT_STRING[self.suit-1])
        else:
            return "XX"


    def cmp(self, other):
        if self.cardvalue < other.cardvalue:
            return -1
        elif self.cardvalue > other.cardvalue:
            return 1
        else:
            if self.suit == other.suit:
                return 0
            elif self.suit < other.suit:
                return -1
            else:
                return 1
    
    def __lt__(self, other):
        return self.cmp(other) < 0
    
    def __eq__(self, other):
        return self.cmp(other) == 0
    
    def __gt__(self, other):
        return self.cmp(other) > 0
    

class PokerHand:
    cards = None

    HIGH_CARD       = 1
    ONE_PAIR        = 2
    TWO_PAIRS       = 3
    THREE_OF_A_KIND = 4
    STRAIGHT        = 5
    FLUSH           = 6
    FULL_HOUSE      = 7
    FOUR_OF_A_KIND  = 8
    STRAIGHT_FLUSH  = 9
    ROYAL_FLUSH     = 10

    def __init__(self, cardstr):
        self.cards = list(map(lambda x: Card(x), cardstr.split(' ')))  # Convert map to list

        if len(self.cards) > 5:
            self.cards = self.cards[0:5]
        elif len(self.cards) < 5:
            for i in range(5 - len(self.cards)):
                self.cards.append(Card())

    def __str__(self):
        return " ".join(map(lambda x: str(x),self.cards))

    def cmp(self, other):
        (self_hand_type,self_high_set_card,self_high_extra) = self.eval_hand()
        (other_hand_type,other_high_set_card,other_high_extra) = other.eval_hand()

        if (self_hand_type < other_hand_type):
            return -1
        elif (self_hand_type > other_hand_type):
            return 1
        else:
            if (self_high_set_card != other_high_set_card):
                for i in range(len(self_high_set_card)):
                    if self_high_set_card[i] < other_high_set_card[i]:
                        return -1
                    else:
                        return 1
            else:
                for i in range(len(self_high_extra)):
                    if self_high_extra[i] < other_high_extra[i]:
                        return -1
                    elif self_high_extra[i] > other_high_extra[i]:
                        return 1

                return 0

    def __lt__(self, other):
        return self.cmp(other) < 0

    def __eq__(self, other):
        return self.cmp(other) == 0
    
    def __gt__(self, other):
        return self.cmp(other) > 0
    
    def sort(self):
        return sorted(self.cards)

    def eval_hand(self):
        hand_type = self.HIGH_CARD
        high_set_card = []
        high_extra_card = []

        if self.is_royal_flush():
            hand_type = self.ROYAL_FLUSH
            high_set_card = [Card.ACE_HIGH]
            high_extra_card = [None]
        elif self.is_straight_flush():
            hand_type = self.STRAIGHT_FLUSH

            sorted_cards = self.sort()

            if sorted_cards[0] == Card.ACE:
                high_set_card = [Card.ACE_HIGH]
            else:
                high_set_card = [sorted_cards[-1].cardvalue]

            high_extra_card = None
        elif self.is_four_of_a_kind():
            hand_type = self.FOUR_OF_A_KIND

            val_counts = self.value_counts()
            keys = self.value_counts().keys()

            for k in keys:

                if val_counts[k] == 4:
                    if (k == Card.ACE):
                        high_set_card = [Card.ACE_HIGH]
                    else:
                        high_set_card = [k]
                else:
                    if (k == Card.ACE):
                        high_extra_card = [Card.ACE_HIGH]
                    else:
                        high_extra_card = [k]

        elif self.is_full_house():
            hand_type = self.FULL_HOUSE

            val_counts = self.value_counts()
            keys = val_counts.keys()

            for k in keys:
                if val_counts[k] == 3:
                    if (k == Card.ACE):
                        high_set_card = [Card.ACE_HIGH]
                    else:
                        high_set_card = [k]
                elif val_counts[k] == 2:
                    if (k == Card.ACE):
                        high_extra_card = [Card.ACE_HIGH]
                    else:
                        high_extra_card = [k]

        elif self.is_flush():
            hand_type = self.FLUSH
            sorted_cards = self.sort()

            if sorted_cards[0].cardvalue == Card.ACE:
                high_set_card = [Card.ACE_HIGH]
                # Convert map to list and reverse
                high_extra_card = list(map(lambda x: x.cardvalue, sorted_cards[1:]))[::-1]
            else:
                high_set_card = [sorted_cards[-1].cardvalue]
                # Convert map to list and reverse
                high_extra_card = list(map(lambda x: x.cardvalue, sorted_cards[:-1]))[::-1]

        elif self.is_straight():
            hand_type = self.STRAIGHT
            sorted_cards = self.sort()

            if sorted_cards[0].cardvalue == Card.ACE and sorted_cards[1].cardvalue == Card.TEN:
                high_set_card = [Card.ACE_HIGH]
                # Convert map to list and reverse
                high_extra_card = list(map(lambda x: x.cardvalue, sorted_cards[1:]))[::-1]
            else:
                high_set_card = [sorted_cards[-1].cardvalue]
                # Convert map to list and reverse
                high_extra_card = list(map(lambda x: x.cardvalue, sorted_cards[:-1]))[::-1]

        elif self.is_three_of_a_kind():
            hand_type = self.THREE_OF_A_KIND

            val_counts = self.value_counts()
            keys = val_counts.keys()

            high_extra_card = []

            for k in keys:
                if val_counts[k] == 3:
                    if k == Card.ACE:
                        high_set_card = [Card.ACE_HIGH]
                    else:
                        high_set_card = [k]
                else:
                    if k == Card.ACE:
                        high_extra_card.append(Card.ACE_HIGH)
                    else:
                        high_extra_card.append(k)

            high_extra_card = sorted(high_extra_card)[::-1]


        elif self.is_two_pair():
            hand_type = self.TWO_PAIRS

            val_counts = self.value_counts()
            keys = val_counts.keys()

            high_set_card = []
            high_extra_card = []

            for k in keys:
                if val_counts[k] == 2:
                    if k == Card.ACE:
                        high_set_card.append(Card.ACE_HIGH)
                    else:
                        high_set_card.append(k)
                else:
                    if k == Card.ACE:
                        high_extra_card.append(Card.ACE_HIGH)
                    else:
                        high_extra_card.append(k)

            high_set_card = sorted(high_set_card)[::-1]
            high_extra_card = sorted(high_extra_card)[::-1]

        elif self.is_pair():
            hand_type = self.ONE_PAIR

            val_counts = self.value_counts()
            keys = val_counts.keys()

            high_set_card = []
            high_extra_card = []

            for k in keys:
                if val_counts[k] == 2:
                    if k == Card.ACE:
                        high_set_card.append(Card.ACE_HIGH)
                    else:
                        high_set_card.append(k)
                else:
                    if k == Card.ACE:
                        high_extra_card.append(Card.ACE_HIGH)
                    else:
                        high_extra_card.append(k)

            high_set_card = sorted(high_set_card)[::-1]
            high_extra_card = sorted(high_extra_card)[::-1]

        else:
            hand_type = self.HIGH_CARD

            high_set_card = [None]
            high_extra_card = []

            keys = self.value_counts().keys()

            for k in keys:
                if k == Card.ACE:
                    high_extra_card.append(Card.ACE_HIGH)
                else:
                    high_extra_card.append(k)

            high_extra_card = sorted(high_extra_card)[::-1]

        return (hand_type,high_set_card,high_extra_card)

    def is_royal_flush(self):
        sorted_cards = self.sort()

        if (self.is_flush() and self.is_straight() and sorted_cards[0].cardvalue == Card.ACE):
            return True
        else:
            return False

    def is_straight_flush(self):
        if (self.is_flush() and self.is_straight()):
            return True
        else:
            return False

    def is_four_of_a_kind(self):
        vals = list(self.value_counts().values())  # Convert dict_values to list
        return vals.count(4) == 1

    def is_three_of_a_kind(self):
        vals = list(self.value_counts().values())  # Convert dict_values to list
        return vals.count(3) == 1

    def is_full_house(self):
        vals = list(self.value_counts().values())  # Convert dict_values to list
        return (vals.count(3) == 1 and vals.count(2) == 1)


    def is_two_pair(self):
        vals = list(self.value_counts().values())  # Convert dict_values to list
        return ((vals.count(3)+vals.count(2)) == 2)


    def is_pair(self):
        vals = list(self.value_counts().values())  # Convert dict_values to list
        return (vals.count(2) > 0)


    def is_straight(self):
        sorted_cards = self.sort()
        # Convert the map object to a list to enable comparison
        diffs = list(map(lambda x, y: x.cardvalue - y.cardvalue, sorted_cards[1:], sorted_cards[:-1]))

        # Check if all differences are 1 (straight) or handle special case for Ace
        return diffs == [1, 1, 1, 1] or (sorted_cards[0].cardvalue == Card.ACE and sorted_cards[1].cardvalue == Card.TEN and diffs == [-9, 1, 1, 1])



    def is_flush(self):
        return self.suit_count() == 1

    def suit_count(self):
        suits = {card.suit for card in self.cards}  # Set comprehension to add suits
        return len(suits)

    def value_counts(self):
        card_values = map(lambda x: x.cardvalue,self.cards)
        value_counts = {}

        for value in card_values:
            if value in value_counts:
                value_counts[value] = value_counts[value] + 1
            else:
                value_counts[value] = 1

        return value_counts

def euler54():
    matchups = open('poker.txt').readlines()
    matchups = map(lambda x: x.strip(),matchups)

    player1Wins = 0
    player2Wins = 0
    ties = 0

    for hand_pair in matchups:
        cards = hand_pair.split(' ')

        hand1 = PokerHand(" ".join(cards[0:5]))
        hand2 = PokerHand(" ".join(cards[5:]))

        if (hand1 > hand2):
            #print("{0} beats {1} -- Player 1 wins".format(hand1,hand2))            
            player1Wins = player1Wins + 1
        elif (hand2 > hand1):
            #print("{0} beats {1} -- Player 2 wins".format(hand2,hand1))
            player2Wins = player2Wins + 1
        else:
            #print("{0} ties {1}".format(hand1,hand2))
            ties = ties + 1

    print(player1Wins)


if __name__ == '__main__':    
    euler54()
    
