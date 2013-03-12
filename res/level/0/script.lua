
function greet_the_world()
	print ("Hello my beloved world!")
	local is_changed = setButtonText("btnNewGame", "It's time to moon some planet!")
	if is_changed == true then
		print ("Successfully changed text of button btnNewGame!")
		if setButtonColor("btnNewGame", "N", 255, 255, 0, 255) == true then
			print ("Zmieniono kolor!")
		end
	else
		print ("Somehow I can't do that!")
	end
	
	nadpisanie()
	addScript("res/level/0/dodatkowy.lua")
	nadpisanie()
	nowa_funkcja()
	print("END of Greet World!")
end

function nadpisanie()
	print("script.lua")
end
