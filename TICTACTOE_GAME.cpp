#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>


using namespace std;

LPSTR NazwaKlasy =  "Klasa Okienka";
MSG Komunikat;

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{

    // WYPEŁNIANIE STRUKTURY
    WNDCLASSEX wc;



    wc.cbSize = sizeof( WNDCLASSEX );
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    //wc.hbrBackground =( HBRUSH )( COLOR_WINDOW + 1 );
    wc.hbrBackground =( HBRUSH )( GetStockObject(GRAY_BRUSH));
    wc.lpszMenuName = NULL;
    wc.lpszClassName = NazwaKlasy;
    wc.hIconSm = LoadIcon( NULL, IDI_APPLICATION );

    // Window registration
    if( !RegisterClassEx( & wc ) )
    {
        MessageBox( NULL, "We cannot registrate this window!", "Unfortunately...",
        MB_ICONEXCLAMATION | MB_OK );
        return 1;
    }

    // Create window
    HWND hwnd;

    hwnd = CreateWindowEx( WS_EX_CLIENTEDGE, NazwaKlasy, "TIC TAC TOE GAME", WS_OVERLAPPEDWINDOW ,
    CW_USEDEFAULT, CW_USEDEFAULT, 900, 600, NULL, NULL, hInstance, NULL );

    if( hwnd == NULL )
    {
        MessageBox( NULL, "We cannot registrate this window!", "Unfortunately", MB_ICONEXCLAMATION );
        return 1;
    }

    ShowWindow( hwnd, nCmdShow );
    UpdateWindow( hwnd );


    while( GetMessage( & Komunikat, NULL, 0, 0 ) )
    {
        TranslateMessage( & Komunikat );
        DispatchMessage( & Komunikat );
    }
    return Komunikat.wParam;
}


const int ROW = 3;
const int COLUMN = 3;
const int COMBO = 3;
const int CELL_SIZE = 600/(ROW+COLUMN);
HBRUSH hbr1, hbr2;
int playerTurn = 1;
int gameBoard[ROW*COLUMN];
int winner = 0;
int wins[ROW];


bool GetGameBoardRect(HWND hwnd, RECT *pRect)
{

	RECT rc;
	if(GetClientRect(hwnd, & rc ))
	   		{
	   			int width = rc.right - rc.left;
	   			int height = rc.bottom - rc.top;

	   			pRect->left = (width - CELL_SIZE*3)/2;
	   			pRect->top = (height - CELL_SIZE*3)/2;
	   			pRect->right = pRect->left + CELL_SIZE*3;
	   			pRect->bottom = pRect->top + CELL_SIZE*3;

/*
	   			pRect->left = (width - CELL_SIZE*4)/2;
	   			pRect->top = (height - CELL_SIZE*4)/2;
	   			pRect->right = pRect->left + CELL_SIZE*4;
	   			pRect->bottom = pRect->top + CELL_SIZE*4;
*/
	   			return TRUE;
	   		}

	SetRectEmpty(pRect);
	return FALSE;

}

void DrawLine(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

int GetCellNumberFromPoint(HWND hwnd, int x, int y)
{
	POINT pt = {x, y};
	RECT rc;

	if (GetGameBoardRect(hwnd, &rc))
	{
		if (PtInRect(&rc, pt))
		{
			// user clicked inside game board
			x = pt.x - rc.left;
			y = pt.y - rc.top;

			int column = x/CELL_SIZE;
			int row = y/CELL_SIZE;

			// convert to index (0 to 8)
			return column + row*3;
		}
	}
	return -1; // outside game board or failure
}

bool GetCellRect(HWND hwnd, int index, RECT * pRect)
{
	RECT rcBoard;

	SetRectEmpty(pRect);

	if (index < 0 || index > 8)
		return FALSE;
	if (GetGameBoardRect(hwnd, &rcBoard))
	{
		// Convert index from 0 to 8 into x,y pair
		int x = index % COLUMN; // Column number
		int y = index / ROW; // Row number

		pRect->left = rcBoard.left + x * CELL_SIZE + 1;
		pRect->top = rcBoard.top + y * CELL_SIZE + 1;
		//pRect->right = rcBoard.left + x * CELL_SIZE;
		//pRect->bottom = rcBoard.top + y * CELL_SIZE;
		pRect->right = pRect->left + CELL_SIZE - 1;
		pRect->bottom = pRect->top + CELL_SIZE - 1;

		return TRUE;
	}


	return FALSE;
}



int GetWinner(int wins[3])
{

	// Horizontal detect
	for (int i = 0; i < 8; i += 3)
	{
		if ((0!=gameBoard[i]) && gameBoard[i] == gameBoard[i+1] && gameBoard[i] == gameBoard[i+2])
		{
			// we have a winner
			wins[0] = gameBoard[i];
			wins[1] = gameBoard[i+1];
			wins[2] = gameBoard[i+2];


			return gameBoard[i];
		}
	}
	// Vertical detect
	for (int i = 0; i < 3; i++)
	{
		if((0!=gameBoard[i]) && gameBoard[i] == gameBoard[i+3] && gameBoard[i] == gameBoard[i+6])
		{
			// we have a winner
			wins[0] = gameBoard[i];
			wins[1] = gameBoard[i+3];
			wins[2] = gameBoard[i+6];

			return gameBoard[i];
		}
	}
	// Diagonal detect
	for (int i = 0; i < 1; i++)
	{
		if((0!=gameBoard[i]) && gameBoard[i] == gameBoard[i+4] && gameBoard[i] == gameBoard[i+8])
		{
			// we have a winner
			wins[0] = gameBoard[i];
			wins[1] = gameBoard[i+4];
			wins[2] = gameBoard[i+8];

			return gameBoard[i];
		}
	}
	// Reverse Diagonal detect
	for (int i = 2; i < 3; i++)
	{
		if((0!=gameBoard[i]) && gameBoard[i] == gameBoard[i+2] && gameBoard[i] == gameBoard[i+4])
		{
			// we have a winner
			wins[0] = gameBoard[i];
			wins[1] = gameBoard[i+2];
			wins[2] = gameBoard[i+4];

			return gameBoard[i];
		}
	}
	// next see if we have any cells empty
	for (int i = 0; i < 9; i++)
		if (0 == gameBoard[i])
			return 0; // continue to play

	return 3; // it's a draw
}

bool get_array(std::vector<int> test)
{
	for (int i = 0; i < COMBO; i++)
	{
		if ((test[i] == 0) || (test[0] != test[i]))
			return false;
	}
	return true;
}



int GetWinner2(int wins[])
{
	std::vector<int> test;
	// Horizontal detect
	for (int i = 0; i < ROW; i++)
		{
			for(int j = 0; j < (COLUMN - COMBO + 1); j++)
			{
				for(int k=0; k < COMBO; k++)
				{
				test.push_back(gameBoard[i * ROW + j + k]);
				if (get_array(test))
				{
							return test[0];
				}
			}
				test.clear();
			}
		}


	// Vertical detect
	for (int i = 0; i < (COLUMN - COMBO + 1); i++)
		{
			for(int j = 0; j < COLUMN; j++)
			{
				for(int k=0; k < COMBO; k++)
				{
				test.push_back(gameBoard[((i + k) * ROW) + j]);
				if (get_array(test))
				{
							return test[0];
				}
			}
				test.clear();
			}
		}

	// Diagonal detect
	for (int i = 0; i < (ROW - COMBO + 1); i++)
		{
			for(int j = 0; j < (COLUMN - COMBO + 1); j++)
			{
				for(int k=0; k < COMBO; k++)
				{
				test.push_back(gameBoard[((i + k) * ROW) + j + k]);
				if (get_array(test))
				{
							return test[0];
				}
			}
				test.clear();
			}
		}

	// Reverse Diagonal detect
	for (int i = 0; i < (ROW - COMBO + 1); i++)
		{
			for(int j = COMBO - 1; j < COLUMN; j++)
			{
				for(int k=0; k < COMBO; k++)
				{
				test.push_back(gameBoard[((i + k) * ROW) + j - k]);
				if (get_array(test))
				{
							return test[0];
				}
			}
				test.clear();
			}
		}


	// next see if we have any cells empty
	for (int i = 0; i < 9; i++)
		if (0 == gameBoard[i])
			return 0; // continue to play

	return 3; // it's a draw
}

bool win(int t[], int g, bool empty)
{
	HWND hwnd;
	bool test;
	int i;
	std::vector<int> test2;

	test = false;


	// Horizontal detect

	for(i = 0; i <= 7; i += 3) test |= ((t[i] == g) && (t[i+1] == g) && (t[i+2] == g));

	// Vertical detect

	for(i = 0; i <= 3; i++)    test |= ((t[i] == g) && (t[i+3] == g) && (t[i+6] == g));

	// Diagonal 0-4-8 detect

	test |= ((t[0] == g) && (t[4] == g) && (t[8] == g));

	// Diagonal 2-4-6 detect

	test |= ((t[2] == g) && (t[4] == g) && (t[6] == g));

	if(test)
	{
		if(!empty)
		{

			MessageBox(hwnd,
					"Player wins",
					"You win",
					MB_OK | MB_ICONEXCLAMATION);
		}
		return true;
	}
	return false;
}


bool draw(int gameBoard[], bool empty)
{
	HWND hwnd;

// Free cells check

  for(int i = 0; i < 9; i++) if(gameBoard[i] == 0) return false;

// No free cells return true and its a draw

  if(!empty)
  {
	  MessageBox(hwnd,
			  	 "No one wins this time",
				 "It's a draw",
	      		  MB_OK | MB_ICONEXCLAMATION);
  }
  return true;
}


// Recursive algorithm MINMAX

int minimax(int gameBoard[], int playerTurn)
{
  int m, mmx;

// Check who wins on the board, return the result


if(win(gameBoard, playerTurn, true)) return (playerTurn == -1) ? 1 : -1;

// Check for draw, return 0

if(draw(gameBoard,true)) return 0;

// Analyze the opponent moves


playerTurn = (playerTurn == -1) ? 1 : -1;


// X(1) - mmx <- -10, max count
// O(2) - mmx <-  10, min count

  mmx = (playerTurn == 1) ? 10 : -10;


// X(1) - mark maximum
// O(2) - mark minimum

  for(int i = 0; i < 9; ++i)
    if(gameBoard[i] == 0)
    {
       gameBoard[i] = playerTurn;
       m = minimax(gameBoard,playerTurn);
       gameBoard[i] = 0;
       if(((playerTurn == 1) && (m < mmx)) || ((playerTurn == -1) && (m > mmx))) mmx = m;
    }
  return mmx;
}

// SI move

int computer(int gameBoard[])
{
  int ruch, i, m, mmx;

  mmx = -10;
  for(i = 0; i < 9; i++)
    if(gameBoard[i] == 0)
    {
      gameBoard[i] = -1;
      m = minimax(gameBoard, -1);
      gameBoard[i] = 0;
      if(m > mmx)
      {
        mmx = m; ruch = i;
      }
    }
  return ruch;
}


// OBSŁUGA ZDARZEŃ
LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{


    switch( msg )
    {

    case WM_CREATE:
    {

    	hbr1 = CreateSolidBrush(RGB(255, 0, 0));
    	hbr2 = CreateSolidBrush(RGB(0, 0, 255));
    	for (int i = 0; i < ROW * COLUMN; i++)
    	{
    		gameBoard[i] = 0;
    	}


    }
    break;

    case WM_LBUTTONDOWN:
    {


    	int xPos = GET_X_LPARAM(lParam);
    	int yPos = GET_Y_LPARAM(lParam);


    	if (0 == playerTurn)
    		break;

    	int index = GetCellNumberFromPoint(hwnd, xPos, yPos);

    	HDC hdc = GetDC(hwnd);


    	if (NULL != hdc)
    	{


    		// Get cell dimension from its index
    		if (index != -1)
    		{
    			RECT rcCell;

    			if ((0==gameBoard[index])  && GetCellRect(hwnd, index, &rcCell))
    			{
    				gameBoard[index] = playerTurn;


    				FillRect(hdc, &rcCell, hbr1);

    				// check for winner
    				winner = GetWinner2(wins);
    				// next see if we have any cells empty



    				if (winner == 1 || winner == -1)
    				{

    					// We have a winner
    					MessageBox(hwnd,
    							  (winner == 1) ? "Player 1 wins" : "Player 2 wins",
    							  "You win",
								  MB_OK | MB_ICONINFORMATION);
    					playerTurn = 0;
    				}
    				else if (3 == winner)
    				{
    					// it's a draw
    					MessageBox(hwnd,
    							  "No one wins this time",
    							  "It's a draw",
    							  MB_OK | MB_ICONEXCLAMATION);
    					playerTurn = 0;
    				}

    				else if (0 == winner)
    				{
    					playerTurn = (playerTurn == 1) ? -1 : 1;
    				}

    			}

    		}

    		ReleaseDC(hwnd, hdc);
    	}
    }
    break;


    case WM_LBUTTONUP:
    {
    	HDC hdc = GetDC(hwnd);

    	int r;


    	if (0 == playerTurn)
    		break;

    	r = computer(gameBoard);


    	if (NULL != hdc)
    	{


    		// Get cell dimension from its index
    		if (r != -1)
    		{
    			RECT rcCell;

    			if ((0==gameBoard[r])  && GetCellRect(hwnd, r, &rcCell))
    			{
    				gameBoard[r] = playerTurn;

     				FillRect(hdc, &rcCell, hbr2);

    				// check for winner
    				winner = GetWinner(wins);
    				if (winner == 1 || winner == -1)
    				{

    					// We have a winner
    					MessageBox(hwnd,
    							  (winner == 1) ? "Player 1 wins" : "Player 2 wins",
    									"You win",
										MB_OK | MB_ICONINFORMATION);
    	    						playerTurn = 0;

    				}
    				else if (3 == winner)
    				{
    					// it's a draw
    					MessageBox(hwnd,
    							"No one wins this time",
								"It's a draw",
								MB_OK | MB_ICONEXCLAMATION);
    					playerTurn = 0;
    				}

    				else if (0 == winner)
    				{
    					playerTurn = (playerTurn == -1) ? 1 : -1;
    				}

    			}

    		}

    		ReleaseDC(hwnd, hdc);
    	}
    }
    break;

    case WM_GETMINMAXINFO:
    {
    	MINMAXINFO * pMinMax = (MINMAXINFO*)lParam;

    	pMinMax->ptMinTrackSize.x = CELL_SIZE * 5;
    	pMinMax->ptMinTrackSize.y = CELL_SIZE * 5;
    }

    break;

    case WM_PAINT:
   	{



   		PAINTSTRUCT ps;
   		HDC hdc = BeginPaint( hwnd, & ps);
   		RECT rc;


   		if (GetGameBoardRect(hwnd, & rc))
   		{

   			Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);


   		for(int i = 0; i < 4; ++i)
   		{

			// Draw Vertical Lines

			DrawLine(hdc, rc.left + CELL_SIZE*i, rc.top, rc.left + CELL_SIZE*i, rc.bottom);

			// Draw Horizontal Lines

			DrawLine(hdc, rc.left, rc.top + CELL_SIZE*i, rc.right, rc.top + CELL_SIZE*i);

   		}
   		// Draw all occupied cells
   		RECT rcCell;
   			for (int i = 0; i < ARRAYSIZE(gameBoard); ++i)
   			{
   				if ((0!=gameBoard[i]) && GetCellRect(hwnd, i, &rcCell))
   				{
   					FillRect(hdc, &rcCell, (gameBoard[i] == 2) ? hbr2 : hbr1);

   				}
   			}
   		}

   		EndPaint( hwnd, & ps); // release hdc


   	}
   	break;

    case WM_CLOSE:
        DestroyWindow( hwnd );
        break;

    case WM_DESTROY:
    	DeleteObject(hbr1);
    	DeleteObject(hbr2);
        PostQuitMessage( 0 );
        break;

        default:
        return DefWindowProc( hwnd, msg, wParam, lParam );
    }



    return 0;
}


