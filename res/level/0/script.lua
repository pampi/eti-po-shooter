intro_sound = false

function greet_the_world()
	print ("Hello my beloved world!")
	local is_changed = setButtonText("btnNewGame", "Dawno dawno temu...\nw krainie calek...\nzyl sobie lord calka...\na stworzyl go wielki latajacy potwor spaghetti...\nT\tBC...")
	if is_changed == true then
		print ("Successfully changed text of button btnNewGame!")
		setButtonColor("btnNewGame", "N", 255, 255, 255, 255)
		setButtonColor("btnNewGame", "H", 0, 0, 255, 255)
	else
		print ("Somehow I can't do that!")
	end
	
	--playSound(music_file, loop)
	if intro_sound == false then
		intro_sound = true
		--playSound("res/audio/temporary_intro_theme.ogg", true)
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
