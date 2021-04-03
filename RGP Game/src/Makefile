rpg: Main.o Puzzles.o Character.o Hero.o Glob.o Mimic.o MapScreen.o InfoBox.o BattleScreen.o CharacterAnimationSet.o Animation.o AnimationManager.o HPBar.o BattleButton.o BattleEffects.o ItemMenu.o
	g++ -o rpg Main.o Puzzles.o Character.o Hero.o Glob.o Mimic.o MapScreen.o InfoBox.o BattleScreen.o CharacterAnimationSet.o Animation.o AnimationManager.o HPBar.o BattleButton.o BattleEffects.o ItemMenu.o -Wall -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

Main.o: Main.cpp 
	g++ -c Main.cpp 

Puzzles.o: Puzzles.cpp Puzzles.hpp
	g++ -c Puzzles.cpp

Character.o: Character.cpp Character.hpp
	g++ -c Character.cpp

Hero.o: Hero.cpp Hero.hpp
	g++ -c Hero.cpp 

Glob.o: Glob.cpp Glob.hpp
	g++ -c Glob.cpp

Mimic.o: Mimic.cpp Mimic.hpp
	g++ -c Mimic.cpp
	
MapScreen.o: MapScreen.cpp MapScreen.hpp MapObject.hpp 
	g++ -c MapScreen.cpp

InfoBox.o: InfoBox.cpp InfoBox.hpp 
	g++ -c InfoBox.cpp

BattleScreen.o: BattleScreen.cpp BattleScreen.hpp
	g++ -c BattleScreen.cpp

CharacterAnimation.o: CharacterAnimationSet.cpp CharacterAnimationSet.hpp
	g++ -c CharacterAnimation.cpp

Animation.o: Animation.cpp Animation.hpp
	g++ -c Animation.cpp

AnimationManager.o: AnimationManager.cpp AnimationManager.hpp
	g++ -c AnimationManager.cpp

HPBar.o: HPBar.cpp HPBar.hpp
	g++ -c HPBar.cpp

BattleButton.o: BattleButton.cpp BattleButton.hpp
	g++ -c BattleButton.cpp

BattleEffects.o: BattleEffects.cpp BattleEffects.hpp
	g++ -c BattleEffects.cpp

ItemMenu.o: ItemMenu.cpp ItemMenu.hpp 
	g++ -c ItemMenu.cpp
	
clean:
	rm *.o  rpg 