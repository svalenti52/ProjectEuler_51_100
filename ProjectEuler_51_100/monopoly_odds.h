#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <random>
#include <queue>

using namespace std;

enum MonoBoard
{	GO, A1, CC1, A2, T1, R1, B1, CH1, B2, B3,
	JAIL, C1, U1, C2, C3, R2, D1, CC2, D2, D3,
	FP, E1, CH2, E2, E3, R3, F1, F2, U2, F3,
	G2J, G1, G2, CC3, G3, R4, CH3, H1, T2, H2
};

vector<string> coded_name = { "GO", "A1", "CC1", "A2", "T1", "R1", "B1", "CH1", "B2", "B3",
							  "JAIL", "C1", "U1", "C2", "C3", "R2", "D1", "CC2", "D2", "D3",
							  "FP", "E1", "CH2", "E2", "E3", "R3", "F1", "F2", "U2", "F3",
							  "G2J", "G1", "G2", "CC3", "G3", "R4", "CH3", "H1", "T2", "H2"};

void monopoly_odds()
{
	vector<double> board_prob(40, 0);
	default_random_engine dre;
	uniform_int_distribution<int> die(1, 4);
	deque<int> cc_q(16, 0);
	deque<int> ch_q(16, 0);

	vector<pair<double, string>> board;
	for (int ix = 0; ix < board_prob.size(); ++ix)
		board.push_back(make_pair(board_prob[ix], coded_name[ix]));

	iota(begin(cc_q), end(cc_q), 1);
	iota(begin(ch_q), end(ch_q), 1);

	int nr_events = 20'000'000;
	int pos = 0;
	++board[pos].first;

	int had_doubles = 0;

	for (int ix = 0; ix < nr_events; ++ix)
	{
		int d1 = die(dre);
		int d2 = die(dre);

		pos += d1 + d2;
		pos %= board_prob.size();

		if (d1 == d2)
		{
			if (had_doubles == 2)
			{
				pos = JAIL;
				had_doubles = 0;
			}
			else
				++had_doubles;
		}
		else
			had_doubles = 0;

		switch (pos)
		{
		case G2J:
			pos = JAIL;
			//had_doubles = 0;
			break;
		case CC1:
		case CC2:
		case CC3:
		{
			//int card_sel = cc(dre);
			int card_sel = cc_q.front();
			cc_q.pop_front();
			cc_q.push_back(card_sel);
			switch (card_sel)
			{
			case 1:
				pos = GO;
				break;
			case 2:
				pos = JAIL;
				//had_doubles = 0;
				break;
			default:
				break;
			}
		}
			break;
		case CH1:
		case CH2:
		case CH3:
		{
			//int card_sel = ch(dre);
			int card_sel = ch_q.front();
			ch_q.pop_front();
			ch_q.push_back(card_sel);
			switch (card_sel)
			{
			case 1:
				pos = GO;
				break;
			case 2:
				pos = JAIL;
				//had_doubles = 0;
				break;
			case 3:
				pos = C1;
				break;
			case 4:
				pos = E3;
				break;
			case 5:
				pos = H2;
				break;
			case 6:
				pos = R1;
				break;
			case 7:
			case 8:
				if (pos == CH1) pos = R2;
				else if (pos == CH2) pos = R3;
				else pos = R1;
				break;
			case 9:
				if (pos == CH1) pos = U1;
				else if (pos == CH2) pos = U2;
				else pos = U1;
				break;
			case 10:
				pos -= 3;
				if (pos == CC3)
				{
					int card_sel = cc_q.front();
					cc_q.pop_front();
					cc_q.push_back(card_sel);
					if (card_sel == 1) pos = GO;
					else if (card_sel == 2) pos = JAIL;
				}
				break;
			default:
				break;
			}
		}
			break;
		default:
			break;
		}
		++board[pos].first;
	}

	for (auto& x : board)
		x.first /= nr_events;

	sort(begin(board), end(board), greater());

	for (auto x : board)
		cout << x.second << ' ' << x.first << '\n';
	cout << '\n';
}
