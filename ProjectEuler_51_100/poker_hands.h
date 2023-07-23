#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <compare>

using namespace std;

using vec_str = vector<string>;

enum HandClass
{
	High,
	OnePair,
	TwoPair,
	ThreeOfKind,
	Straight,
	Flush,
	FullHouse,
	FourOfKind,
	StraightFlush,
	RoyalFlush
};

vector<int> how;

int count_ties = 0;

bool operator < (HandClass c1, HandClass c2)
{
	return c1 < c2;
}

bool gt(char c1, char c2)
{
	if (c1 == 'A' && c2 != 'A') return true;
	if (c1 != 'A' && c2 == 'A') return false;
	if (c1 == 'K' && c2 != 'K') return true;
	if (c1 != 'K' && c2 == 'K') return false;
	if (c1 == 'Q' && c2 != 'Q') return true;
	if (c1 != 'Q' && c2 == 'Q') return false;
	if (c1 == 'J' && c2 != 'J') return true;
	if (c1 != 'J' && c2 == 'J') return false;
	if (c1 == 'T' && c2 != 'T') return true;
	if (c1 != 'T' && c2 == 'T') return false;
	return c1 > c2;
}

bool order_rank_more(string& s1, string& s2)
{
	if (s1[0] == 'A' && s2[0] != 'A') return true;
	if (s1[0] != 'A' && s2[0] == 'A') return false;
	if (s1[0] == 'A' && s2[0] == 'A') return false;

	if (s1[0] == 'K' && s2[0] != 'K') return true;
	if (s1[0] != 'K' && s2[0] == 'K') return false;
	if (s1[0] == 'K' && s2[0] == 'K') return false;

	if (s1[0] == 'Q' && s2[0] != 'Q') return true;
	if (s1[0] != 'Q' && s2[0] == 'Q') return false;
	if (s1[0] == 'Q' && s2[0] == 'Q') return false;

	if (s1[0] == 'J' && s2[0] != 'J') return true;
	if (s1[0] != 'J' && s2[0] == 'J') return false;
	if (s1[0] == 'J' && s2[0] == 'J') return false;

	if (s1[0] == 'T' && s2[0] != 'T') return true;
	if (s1[0] != 'T' && s2[0] == 'T') return false;
	if (s1[0] == 'T' && s2[0] == 'T') return false;

	if (s1[0] > s2[0]) return true;
	return false;
}

bool isPair(vec_str& hand)
{
	for (int card = 0; card < 4; ++card)
		if (hand[card][0] == hand[card + 1][0]) return true;
	return false;
}

bool resolvePair(vec_str& h1, vec_str& h2)
{
	int card1 = 0;
	for (int card = 0; card < 4; ++card)
		if (h1[card][0] == h1[card + 1][0])
		{
			card1 = card;
			break;
		}

	int card2 = 0;
	for (int card = 0; card < 4; ++card)
		if (h2[card][0] == h2[card + 1][0])
		{
			card2 = card;
			break;
		}

	if (gt(h1[card1][0], h2[card2][0])) return true;
	return false;
}

bool isTwoPair(vec_str& hand)
{
	if (hand[0][0] == hand[1][0] && hand[2][0] == hand[3][0]) return true;
	if (hand[1][0] == hand[2][0] && hand[3][0] == hand[4][0]) return true;
	if (hand[0][0] == hand[1][0] && hand[3][0] == hand[4][0]) return true;
	return false;
}

bool resolveTwoPair(vec_str& h1, vec_str& h2)
{
	if (gt(h1[1][0], h2[1][0])) return true;
	if (gt(h2[1][0], h1[1][0])) return false;

	if (gt(h1[3][0], h2[3][0])) return true;
	if (gt(h2[3][0], h1[3][0])) return false;
	
	if (h1[3][0] == h2[3][0]) ++count_ties;

	return false;
}

bool isThreeOfKind(vec_str& hand)
{
	if (hand[0][0] == hand[1][0] && hand[0][0] == hand[2][0]) return true;
	if (hand[1][0] == hand[2][0] && hand[1][0] == hand[3][0]) return true;
	if (hand[2][0] == hand[3][0] && hand[2][0] == hand[4][0]) return true;
	return false;
}

bool resolveThreeOfKind(vec_str& h1, vec_str& h2)
{
	if (gt(h1[2][0], h2[2][0])) return true;
	return false;
}

bool isFlush(vec_str& hand)
{
	char c = hand[0][1];
	for (string& s : hand)
		if (c != s[1])
			return false;
	return true;
}

bool isStraight(vec_str& hand)
{
	if (hand[0][0] == 'A')
	{
		if (hand[1][0] == 'K')
		{
			if (hand[2][0] != 'Q') return false;
			if (hand[3][0] != 'J') return false;
			if (hand[4][0] != 'T') return false;
			return true;
		}
		else if (hand[1][0] == '5')
		{
			if (hand[2][0] != '4') return false;
			if (hand[3][0] != '3') return false;
			if (hand[4][0] != '2') return false;
			return true;
		}
		return false;
	}

	if (hand[0][0] == 'K')
	{
		if (hand[1][0] != 'Q') return false;
		if (hand[2][0] != 'J') return false;
		if (hand[3][0] != 'T') return false;
		if (hand[4][0] != '9') return false;
		return true;
	}

	if (hand[0][0] == 'Q')
	{
		if (hand[1][0] != 'J') return false;
		if (hand[2][0] != 'T') return false;
		if (hand[3][0] != '9') return false;
		if (hand[4][0] != '8') return false;
		return true;
	}

	if (hand[0][0] == 'J')
	{
		if (hand[1][0] != 'T') return false;
		if (hand[2][0] != '9') return false;
		if (hand[3][0] != '8') return false;
		if (hand[4][0] != '7') return false;
		return true;
	}

	if (hand[0][0] == 'T')
	{
		if (hand[1][0] != '9') return false;
		if (hand[2][0] != '8') return false;
		if (hand[3][0] != '7') return false;
		if (hand[4][0] != '6') return false;
		return true;
	}

	if (hand[0][0] == '9' || hand[0][0] == '8' || hand[0][0] == '7' || hand[0][0] == '6')
	{
		for (char cx = 1; cx <= 4; ++cx)
			if (hand[cx][0] != hand[0][0] - cx) return false;
		return true;
	}

	return false;
}

bool isRoyalFlush(vec_str& hand)
{
	if (!isFlush(hand)) return false;
	if (hand[0][0] != 'A') return false;
	if (hand[1][0] != 'K') return false;
	if (hand[2][0] != 'Q') return false;
	if (hand[3][0] != 'J') return false;
	if (hand[4][0] != 'T') return false;
	return true;
}

bool isStraightFlush(vec_str& hand)
{
	if (!isFlush(hand)) return false;
	return isStraight(hand);
}

bool resoveStraightFlushes(vec_str& h1, vec_str& h2)
{
	if (h1[0][0] > h2[0][0]) return true;
	return false;
}

bool isFourOfKind(vec_str& hand)
{
	if (hand[0][0] == hand[1][0] && hand[1][0] == hand[2][0] && hand[2][0] == hand[3][0]) return true;
	if (hand[1][0] == hand[2][0] && hand[2][0] == hand[3][0] && hand[3][0] == hand[4][0]) return true;
	return false;
}

bool resolveFourOfKind(vec_str& h1, vec_str& h2)
{
	if (h1[2][0] > h2[2][0]) return true;
	return false;
}

bool isFullHouse(vec_str& hand)
{
	if (hand[0][0] != hand[1][0]) return false;
	if (hand[3][0] != hand[4][0]) return false;
	if (hand[2][0] != hand[0][0] && hand[2][0] != hand[4][0]) return false;
	return true;
}

bool resolveFullHouse(vec_str& h1, vec_str& h2)
{
	if (gt(h1[2][0], h2[2][0])) return true;
	return false;
}

bool poker_eval_for_h1(vec_str& h1, vec_str& h2)
{
	if (isRoyalFlush(h1) && !isRoyalFlush(h2)) return true;
	if (!isRoyalFlush(h1) && isRoyalFlush(h2)) return false;

	if (isStraightFlush(h1) && !isStraightFlush(h2)) return true;
	if (!isStraightFlush(h1) && isStraightFlush(h2)) return false;
	if (isStraightFlush(h1) && isStraightFlush(h2)) return resoveStraightFlushes(h1, h2);

	if (isFourOfKind(h1) && !isFourOfKind(h2)) return true;
	if (!isFourOfKind(h1) && isFourOfKind(h2)) return false;
	if (isFourOfKind(h1) && isFourOfKind(h2)) return resolveFourOfKind(h1, h2);

	if (isFullHouse(h1) && !isFullHouse(h2)) return true;
	if (!isFullHouse(h1) && isFullHouse(h2)) return false;
	if (isFullHouse(h1) && isFullHouse(h2)) return resolveFullHouse(h1, h2);

	if (isFlush(h1) && !isFlush(h2)) return true;
	if (!isFlush(h1) && isFlush(h2)) return false;
	if (isFlush(h1) && isFlush(h2)) ++count_ties;

	if (isStraight(h1) && !isStraight(h2)) return true;
	if (!isStraight(h1) && isStraight(h2)) return false;
	if (isStraight(h1) && isStraight(h2)) ++count_ties;

	if (isThreeOfKind(h1) && !isThreeOfKind(h2)) return true;
	if (!isThreeOfKind(h1) && isThreeOfKind(h2)) return false;
	if (isThreeOfKind(h1) && isThreeOfKind(h2)) return resolveThreeOfKind(h1, h2);

	if (isTwoPair(h1) && !isTwoPair(h2)) return true;
	if (!isTwoPair(h1) && isTwoPair(h2)) return false;
	if (isTwoPair(h1) && isTwoPair(h2)) return resolveThreeOfKind(h1, h2);

	if (isPair(h1) && !isPair(h2)) return true;
	if (!isPair(h1) && isPair(h2)) return false;
	if (isPair(h1) && isPair(h2)) return resolvePair(h1, h2);

	for (int card = 0; card < 5; ++card)
	{
		if (gt(h1[card][0], h2[card][0])) return true;
		else if (gt(h2[card][0], h1[card][0])) return false;
	}

	return false;
}

ostream& operator << (ostream& oss, vec_str& vs)
{
	for (string& s : vs)
		oss << s << ' ';
	return oss;
}

void poker_hands()
{
	ifstream in("poker.txt");

	vec_str vs = {"", "", "", "", "",   "", "", "", "", ""};

	vector<vec_str> hand1;
	vector<vec_str> hand2;

	count_ties = 0;

	int hand_counter = 0;

	while (!in.eof())
	{
		for (string& s : vs)
			in >> s;

		vec_str hand_tmp1;
		vec_str hand_tmp2;
		for (int ix = 0; ix < vs.size() / 2; ++ix)
			hand_tmp1.emplace_back(vs[ix]);
		hand1.emplace_back(hand_tmp1);
		for (int ix = vs.size() / 2; ix < vs.size(); ++ix)
			hand_tmp2.emplace_back(vs[ix]);
		hand2.emplace_back(hand_tmp2);
	}

	for (vec_str& vs : hand1)
		sort(vs.begin(), vs.end(), order_rank_more);

	for (vec_str& vs : hand2)
		sort(vs.begin(), vs.end(), order_rank_more);

	cout << hand1.size() << "  " << hand2.size() << '\n';

	vec_str result;
	
	how.clear();
	int count = 0;
	int zero = 0; // hand1.size() - 2;
	for (int hx = zero; hx < hand1.size(); ++hx)
		if (poker_eval_for_h1(hand1[hx], hand2[hx]))
		{
			result.emplace_back("Won");
			++count;
		}
		else
			result.emplace_back("Lost");

	for (int hx = zero; hx < hand1.size(); ++hx)
		cout << hand1[hx] << ' ' << hand2[hx] << "  " << result[hx] << '\n';

	cout << "Winning hands for Player 1 = " << count << '\n';
	cout << "Ties to be resolved = " << count_ties << '\n';
}
