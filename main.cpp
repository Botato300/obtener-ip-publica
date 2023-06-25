#include <iostream>
#include <windows.h>
#include <winhttp.h>

int main()
{
    DWORD dwSize = 0, dwDownloaded = 0;
    LPSTR pszOutBuffer;
    BOOL bResults = FALSE;
    HINTERNET hSession = NULL, hConnect = NULL, hRequest = NULL;

    hSession = WinHttpOpen(L"Check IP/1.0", WINHTTP_ACCESS_TYPE_NO_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, WINHTTP_FLAG_ASYNC);

    if(hSession) hConnect = WinHttpConnect(hSession, L"checkip.amazonaws.com", INTERNET_DEFAULT_HTTPS_PORT, 0);

    if(hConnect) hRequest = WinHttpOpenRequest(hConnect, L"GET", NULL, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
    
    if(hRequest) bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);

    if(bResults) bResults = WinHttpReceiveResponse(hRequest, NULL);

    if(bResults)
    {
        do 
        {
            dwSize = 0;
            if(!WinHttpQueryDataAvailable(hRequest, &dwSize)) 
            {
                std::cout<<"ERROR: "<<GetLastError()<<" en WinHttpQueryDataAvailable.\n";
                break;
            }
            
            if(!dwSize) break;

            pszOutBuffer = new char[dwSize+1];
            if(!pszOutBuffer)
            {
                std::cout<<"ERROR: Sin memoria.\n";
                break;
            }
            
            ZeroMemory(pszOutBuffer, dwSize+1);

            if(!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded))
            {                                  
                std::cout<<"ERROR: "<<GetLastError()<<" en WinHttpReadData.\n";
            }
            else
            {
                std::cout<<"Tu IP es: "<<pszOutBuffer;
            }
        
            delete[] pszOutBuffer;

            if(!dwDownloaded) break;
                
        } while(dwSize > 0);
    }
    else
    {
        std::cout<<"Un error "<<GetLastError()<<" ha ocurrido.\n";
    }

    if(hRequest) WinHttpCloseHandle(hRequest);
    if(hConnect) WinHttpCloseHandle(hConnect);
    if(hSession) WinHttpCloseHandle(hSession);

    system("pause");
	return 0;
}