/*
  Using MinHook 1.3.3 (https://github.com/TsudaKageyu/minhook)
  This simple hook was written by Kiko but could've been done by almost anyone understanding hooks.
  I've decided to comment some code to help newbies learn.
  Enjoy!
*/
int MessageBoxA_c;

/*
  Parameters straight from some C++ file.
  I did ctrl + click on MessageBoxA to get these parameters. (for newbies)
*/
int WINAPI MessageBoxA_r(
    _In_opt_ HWND hWnd,
    _In_opt_ LPCSTR lpText,
    _In_opt_ LPCSTR lpCaption,
    _In_ UINT uType)
{
    /*  
      We disable the hook so that it doesn't infinite loop while calling the real MessageBoxA.
      Why don't we use the backup we created? (MessageBoxA_c)
      Because it crashes and I'm too lazy to find out why so I just replaced it with a simple solution.
    */
    MH_DisableHook(&MessageBoxA);

    // There was no need to cast it to a char but I wanted to keep it clean.
    // strcmp (short for string compare) compares two parameters. Const chars of course.
    if (strcmp(reinterpret_cast<const char*>(lpText), "An unexpected error occurred and Roblox needs to quit.  We're sorry!") == 0)
    {
        // You can modify these arguments how you would like.
        // Even adding Yes/No buttons is possible with questions and input.
        // If you're adding a NOP to every instruction in the function this is where you should do it. (To avoid crash logs being uploaded)
        // Using FFlags is a lot smarter though, you should check it out.
        int MessageBoxReturn = MessageBoxA(hWnd, "It seems like the client crashed.", "MessageBoxA Hook", uType);
        return MessageBoxReturn; // Since we know the arguments of Roblox's MessageBoxA and that they don't modify arguments for it to return anything we don't need this. But I will keep it.
    }
    int MessageBoxReturn = MessageBoxA(hWnd, lpText, lpCaption, uType); // Call original MessageBoxA with the hook disabled from before.
    MH_EnableHook(&MessageBoxA); // Enable the hook after we call the original function without a hook enabled.
    return MessageBoxReturn; // Just to be on the safe side.
}



int main()
{
    ConsoleBypass("MessageBoxA - Hook"); // The console bypass is not included. It's outdated and can be found in any leaked source code.
    printf("Response from application.\n");

    /* Just to make sure we're on the safe side */
    if (MH_Initialize() != MH_OK)
    {
        printf("Failed to load hooking library.\n");
        return NULL;
    }
    /* 
      There are sometimes issues with hooking some functions so we make sure there aren't any. 
      MessageBoxA_c isn't really used since it crashes. That's why we disable the hook before calling the function.
      The hook will be enabled right after that.
     */
    if (MH_CreateHook(&MessageBoxA, &MessageBoxA_r, reinterpret_cast<LPVOID*>(MessageBoxA_c)) != MH_OK)
    {
        printf("Failed to place hook.\n");
        return NULL;
    }
    /* If above doesn't error then this shouldn't either.. but you never know */
    if (MH_EnableHook(&MessageBoxA) != MH_OK)
    {
        printf("Failed to enable hook.\n");
        return NULL;
    }

    /* 
      This function pointer uses __fastcall instead of it's real calling conv- that's why we use it to crash Roblox so that the message appears.
      If you're using the code, remove the line under this since I just use it to create a crash.
    */
    r_lua_typename(NULL, 1);
}
