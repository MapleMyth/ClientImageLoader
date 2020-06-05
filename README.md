Hey everyone! its Arufonsu/Thora, you probably heard a bit from me as a small Contributor in HeavenMS... Anyway..

# Client Image Loader
Client Image Loader is a DLL that can be injected into a MapleStory v83 client to load from image data files.

## What
 This will make your MapleStory v83 client load from "*.img" files inside a data directory "./Data" instead of "*.wz" compressed files at the index.
 
## Why
There are a couple of advantages especially for WZ editors trying to get new content to work in older versions.

 - Eliminate the GFX glitches and memory leaks making the client more stable.
- Push file updates and patches to your users faster, easier and less bandwidth consuming.
-  Your game installation directory and file structure will look well organized.
- It's cool and interesting?

## How
1. You can compile this with VS 2015+ (i used Community). After you compile this project (resulting in a .DLL file) you need to inject it. Now, there are many ways to inject a .DLL file to your MapleStory client but this project is already configured with the APIDummy export method.
 
2. Download CFF Explorer.
 
3. Go to "File > Open" and select your "ijl15.dll" inside your MapleStory directory.
 
4. Proceed to "Import Adder" and nearby the modules box, click "Add" to select the previously compiled .DLL file.

5. Import the "APIDummy" from Exported functions to Imported functions, by Name or by Ordinal, any of them will work just fine. <img src="https://i.imgur.com/sW2tKNQ.png"  height="auto">

6. Click "Rebuild Import Table" then save the file, you can overwrite the one in your MS Folder if you want, make sure you have a backup.

7. Make sure that you have both: the compiled .dll and modified ijl15.dll in your MS v83 Folder.

8. Use [Stredit](http://forum.ragezone.com/f921/release-stredit-localhost-editor-810762/) to modify your v83 client's strings "../Data" and "../DataT" to "Data" and "DataT".  (IDs: 2294 and 2295).
 
9. Now your client should automatically load with the compiled .DLL injected and hooked to ijl15.dll

## Lets try it!
Now, make sure that you have List.wz in the same folder of your client.exe and the generated .dll hooked to your Ijl15.dll.
Try to make it so you have the following structure:

<img src="https://i.imgur.com/Jr5tGFb.png"  height="auto">


Now run your v83 game client and see the "magic" happen!
<img src="https://i.imgur.com/UhZbDD6.png"  height="auto">

This has been tested using HeavenMS (Credits to @[**Ronan**](https://github.com/ronancpl/HeavenMS/))


## Credits for Img Loading
@[**MapleMyth**](https://github.com/MapleMyth/) ~ forked from MapleMyth/ClientImageLoader

@[**Feras**](http://forum.ragezone.com/members/2000265649.html) ~ hints for v83 support.

@[**XIEJIASHU**](http://forum.ragezone.com/members/2000286887.html) ~ stdcall issue in IWzResMan_SetResMan.

@[**buttbeam**](http://forum.ragezone.com/members/2000258756.html) ~ Everything? [Released this](https://gist.github.com/y785/3f13026d33b5a7f0edab0bd60f4eed36).

@[**Darter**](http://forum.ragezone.com/members/450249.html) ~ This project is based on his [AuthHook](https://github.com/RajanGrewal/AuthHook/) release.

@[**Eric**](http://forum.ragezone.com/members/801110.html "Eric is online now") ~ MapleMyth [learnt a lot](http://forum.ragezone.com/f921/src-universal-localhost-enabler-1137639-post8872554/#post8872554) from him.

@[**Diamondo25**](http://forum.ragezone.com/members/437824.html) ~ Stredit (2.9.5.0)
