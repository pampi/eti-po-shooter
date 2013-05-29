intro_sound = true
idle_x = 0.0
idle_y = 500.0

anim_staying = 1
anim_left = 2
anim_right = 3
anim_up = 4
anim_down = 5

-- Stany gry
game_notSure = 0
game_loading = 1
game_pause = 2
game_idle = 3
game_playing = 4
game_showingmenu = 5
game_gameOver = 6
game_abandon_error = 7
game_exiting = 8

function backToBack()
	print ("Wracamy do poziomu 0")
	stopSoundAll()
	changeLevel(0)
	changeGameState(game_showingmenu)
end 

-- if addTextBox("cosTam", "Example", 24, 500.0, 0.0) == true then
	-- print ("Dodany przycisk!")
-- else
	-- print ("Somehow fail!")
-- end



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
	--playSound("res/audio/mainmenu.ogg", true)


end

function startNewGame()
    print ("Czas zaczac nowa gre!")
	stopSoundAll()
	changeLevel(1)
	changeGameState(game_playing)
end

function zegnajSwiecie()
	stopSoundAll()
	changeGameState(game_exiting)
	print ("Papa swiecie")
end

