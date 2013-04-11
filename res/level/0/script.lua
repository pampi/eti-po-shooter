intro_sound = false
idle_x = 0.0
idle_y = 500.0

if addTextBox("cosTam", "Example", 24, 500.0, 0.0) == true then
	print ("Dodany przycisk!")
else
	print ("Somehow fail!")
end

function startIdleAction()
	if setGUIHide("txtIdle", false) == false then
		print ("StartIdle")
		addTextBox("txtIdle", "IDLE State", 24, 400, 300)
	else
		print ("StartIdle2")
	end
end

function performIdleAction()
	idle_x = idle_x + 5.0
	if idle_x > 1200.0 then
		idle_x = 0.0
	end
	setGUIPosition("txtIdle", idle_x, idle_y)
end

function stopIdleAction()
	print ("Stop Idle!")
	if setGUIHide("txtIdle", true) == false then
		print("Can't hide txtIdle!")
	end
end

function greet_the_world()
	print ("Hello my beloved world!")
	--local is_changed = setButtonText("btnNewGame", "It's time to moon some planet!")
	if is_changed == true then
		print ("Successfully changed text of button btnNewGame!")
		setGUIColor("btnNewGame", "N", 255, 255, 255, 255)
		setGUIColor("btnNewGame", "H", 0, 0, 255, 255)
	else
		print ("Somehow I can't do that!")
	end
	
	--playSound(music_file, loop)
	if intro_sound == false then
		intro_sound = true
		playSound("res/audio/Romeointro.ogg", true)
	end
--	nadpisanie()
--	addScript("res/level/0/dodatkowy.lua")
--	nadpisanie()
--	nowa_funkcja()
--	print("END of Greet World!")
end

function startNewGame()
        print ("Czas zaczac nowa gre!")
	stopSoundAll()
        changeLevel(1)
end

function nadpisanie()
	print("script.lua")
end

function zegnajSwiecie()
	stopSound("res/audio/temporary_intro_theme.ogg")
	print ("Papa swiecie")
end
