// Dota2AutoJoin.cpp : Run after starting/searching for Dota2 game - leave Dota2 window open/focused. 
//						Will AutoJoin game when found and send message.
//

#include "Main.h"
#include "WinHttpClient.h"

//FUNCTIONS
void startAutoJoin();
int getPixelColor(HDC dc);
void clickMouse(int x, int y);
void clickKey(char keyval);
//screen capture
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
void BitmapToJpg(HBITMAP hbmpImage, int width, int height);
bool ScreenCapture(int x, int y, int width, int height, char *filename);

int main()
{
	/*WinHttpClient client(L"http://localhost:8080/hello-user/greeting");
	string data = "test=omgitworked";
	client.SetAdditionalDataToSend((BYTE *)data.c_str(), data.size());

	// Set request headers.
	wchar_t szSize[50] = L"";
	swprintf_s(szSize, L"%d", data.size());
	wstring headers = L"Content-Length: ";
	headers += szSize;
	headers += L"\r\nContent-Type: application/x-www-form-urlencoded\r\n";
	client.SetAdditionalRequestHeaders(headers);

	// Send HTTP post request.
	client.SendHttpRequest(L"POST");

	wstring httpResponseHeader = client.GetResponseHeader();
	wstring httpResponseContent = client.GetResponseContent();
	**/
	cout << "Dota2 Auto Join..." << endl << "Type s to start, x to exit." << endl;
	char input;
	do {
		cin >> input;

		if (input == 's' || input == 'S') {
			startAutoJoin();
			input = 'x';
		}
	} while (input != 'x');

	cout << "Exiting..." << endl;
	_sleep(2000);

    return EXIT_SUCCESS;
}

void startAutoJoin() 
{
	//get pixel color
	//if green accept match
	int found = 0;

	cout << "--Started--" << endl << "--Checking for match to be found...." << endl;

	//Start thread for screen shot caps

	HDC dc = GetDC(NULL);

	
	do {
		found = getPixelColor(dc);
		_sleep(2000);
	} while (found != 2);

	ReleaseDC(NULL, dc);

	cout << "--Match Found..." << endl;
	//found match now accept
	//clickKey(VK_RETURN);
	clickMouse(1132, 702);

	cout << "--Accepted Match..." << endl;

	cout << "--The match is now loading." << endl << "-------------" << endl;
	//screen shot every 20 seconds until user closes

	// Initialize GDI+.
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	int x1 = 0;
	int y1 = 0;
	int x2 = GetSystemMetrics(SM_CXSCREEN);
	int y2 = GetSystemMetrics(SM_CYSCREEN);

	while (true) {
		ScreenCapture(x1, y1, x2 - x1, y2 - y1, "screen.jpg");
		cout << "Sleeping for 10 seconds...." << endl;
		_sleep(10000);
	}

	//Shutdown GDI+
	GdiplusShutdown(gdiplusToken);
}

int getPixelColor(HDC dc)
{
	COLORREF color;
	int found = 0;

	/* debug 
	POINT p;
	GetCursorPos(&p);
	COLORREF color = GetPixel(dc, p.x, p.y);
	cout << p.x << "," << p.y << " | ";
	cout << (int)GetRValue(color) << "," << (int)GetGValue(color) << "," << (int)GetBValue(color) << endl;
	*/

	color = GetPixel(dc, 1132, 702);   // ACTUAL: 1132, 702
	cout << "green: " << (int)GetRValue(color) << "," << (int)GetGValue(color) << "," << (int)GetBValue(color) << endl;
	if (((int)GetRValue(color) >= 54 && (int)GetRValue(color) <= 58)
			&& ((int)GetGValue(color) >= 85 && (int)GetGValue(color) <= 89)
			&& ((int)GetBValue(color) >= 71 && (int)GetBValue(color) <= 75)) {
		
		cout << "match green check" << endl;
		found++;
	}

	color = GetPixel(dc, 1353, 691);  // ACTUAL: 1353, 691
	cout << "white: " << (int)GetRValue(color) << "," << (int)GetGValue(color) << "," << (int)GetBValue(color) << endl;
	if (((int)GetRValue(color) >= 255 && (int)GetRValue(color) <= 255)
		&& ((int)GetGValue(color) >= 255 && (int)GetGValue(color) <= 255)
		&& ((int)GetBValue(color) >= 255 && (int)GetBValue(color) <= 255)) {

		cout << "match white check" << endl;
			found++;
	}

	return found;
}

void clickMouse(int x, int y)
{
	//set mouse location to accept area
	SetCursorPos(x, y);
	INPUT input = { 0 };
	//left down
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	::SendInput(1, &input, sizeof(INPUT)); //:: sets this to use global namespace

	::ZeroMemory(&input, sizeof(INPUT));
	//left up
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1, &input, sizeof(INPUT));
}

void clickKey(char keyval)
{
	//Structure for keyboard event
	INPUT ip;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press the key
	ip.ki.wVk = keyval;  //0x41;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	_sleep(30);

	// Release the key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
}




int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT num = 0;          // number of image encoders
	UINT size = 0;         // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if (size == 0)
	{
		return -1;  // Failure
	}

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
	{
		return -1;  // Failure
	}

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}

	free(pImageCodecInfo);
	return -1;  // Failure
}

void BitmapToJpg(HBITMAP hbmpImage, int width, int height)
{
	Bitmap *p_bmp = Bitmap::FromHBITMAP(hbmpImage, NULL);
	//Bitmap *p_bmp = new Bitmap(width, height, PixelFormat32bppARGB);

	CLSID pngClsid;
	int result = GetEncoderClsid(L"image/jpeg", &pngClsid);
	if (result != -1)
		std::cout << "Encoder succeeded" << std::endl;
	else
		std::cout << "Encoder failed" << std::endl;
	p_bmp->Save(L"C:\\Users\\Curtis\\Documents\\DEV\\images\\screen.jpg", &pngClsid, NULL);
	delete p_bmp;
}

bool ScreenCapture(int x, int y, int width, int height, char *filename)
{
	HDC hDc = CreateCompatibleDC(0);
	HBITMAP hBmp = CreateCompatibleBitmap(GetDC(0), width, height);
	SelectObject(hDc, hBmp);
	BitBlt(hDc, 0, 0, width, height, GetDC(0), x, y, SRCCOPY);
	BitmapToJpg(hBmp, width, height);
	DeleteObject(hBmp);
	return true;
}
