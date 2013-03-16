
function greet_the_world()
	print ("Hello my beloved world!")
	--local is_changed = setButtonText("btnNewGame", "It's time to moon some planet!")
	if is_changed == true then
		print ("Successfully changed text of button btnNewGame!")
		setButtonColor("btnNewGame", "N", 255, 255, 255, 255)
		setButtonColor("btnNewGame", "H", 0, 0, 255, 255)
	else
		print ("Somehow I can't do that!")
	end
	
--	nadpisanie()
--	addScript("res/level/0/dodatkowy.lua")
--	nadpisanie()
--	nowa_funkcja()
--	print("END of Greet World!")
end

function startNewGame()
        print ("Czas zaczac nowa gre!")
        changeLevel(1)
end

function nadpisanie()
	print("script.lua")
end

function zegnajSwiecie()
	print ("Papa swiecie")
end
