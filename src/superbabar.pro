#-------------------------------------------------
#
# Project created by berardg 2011-05-17T11:16:03
#
#-------------------------------------------------

QT -= network
QT -= gui
QT -= core

TARGET = ../superbabar
TEMPLATE = app

win32 {
		LIBS = -L../lib/SFMLwin \
                -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio \
                -lglu32 -lopengl32

		INCLUDEPATH = .
		DEPENDPATH = . SFML
		DEFINES = SFML_DYNAMIC
}

unix {

    contains ( CROSS_COMPILE, yes ) {

        LIBS += -L../lib/SFMLwin \
                -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio \
                -lglu32 -lopengl32

        INCLUDEPATH += .

        DEPENDPATH += . SFML

        DEFINES += SFML_DYNAMIC

        QMAKE_CC = i586-mingw32msvc-gcc
        QMAKE_CXX = i586-mingw32msvc-g++
        QMAKE_LINK = i586-mingw32msvc-g++

    } else {

	QT_INSTALL_PREFIX = $$[QT_INSTALL_PREFIX]
	X64 = $$find(QT_INSTALL_PREFIX, 64)
	isEmpty(X64) {		
	  	LIBS += -L"../lib/gcc/x32" 
		QMAKE_LFLAGS_RPATH += -L"../lib/gcc/x32" 
	} else {
                LIBS += -L../lib/gcc/x64 -L/usr/lib64 -lGL
                QMAKE_LFLAGS_RPATH += -L../lib/gcc/x64
	}
	QMAKE_LFLAGS += -g 	
	QMAKE_CFLAGS += -g
	QMAKE_CXXFLAGS += -g

        LIBS +=  -L"../lib/gcc"\
	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	
    }
 
    DESTDIR = ./
    OBJECTS_DIR = release/.obj
    MOC_DIR = release/.moc
    RCC_DIR = release/.rcc
    UI_DIR = release/.ui

}

INCLUDEPATH += ../lib/include

SOURCES += \
    actors/WalkingMonster.cpp \
    actors/Rocket.cpp \
    actors/RemoteBabar.cpp \
    actors/ProjectilesManager.cpp \
    actors/Projectile.cpp \
    actors/MonstersManager.cpp \
    actors/Monster.cpp \
    actors/FollowingWalkingMonster.cpp \
    actors/FollowingFlyingMonster.cpp \
    actors/FlyingMonster.cpp \
    actors/Explosion.cpp \
    actors/ElmarTile.cpp \
    actors/ChargingMonster.cpp \
    actors/BossElmar.cpp \
    actors/Boss.cpp \
    actors/Babar.cpp \
    actors/Actor.cpp \
    AI/AI.cpp \
    control/SfmlKeyConvertor.cpp \
    control/KeyboardConfig.cpp \
    control/Keyboard.cpp \
    control/InputString.cpp \
    control/EventKeyboard.cpp \
    events/Triggerable.cpp \
    events/Trigger.cpp \
    events/Stats.cpp \
	controllers/ActionController.cpp \
	controllers/NetworkActionController.cpp \
	controllers/KeyboardActionController.cpp \
	controllers/MenuKeyboardActionController.cpp \
	controllers/PlayerKeyboardActionController.cpp \
	controllers/NetworkMenuActionController.cpp \
	controllers/NetworkPlayerActionController.cpp \
	controllers/NetworkRemotePlayerActionController.cpp \
	controllers/NetworkLocalPlayerActionController.cpp \
    events/EventsManager.cpp \
    events/Event.cpp \
    game/StaticData.cpp \
    game/LevelsManager.cpp \
    game/GameInitializer.cpp \
    game/GameEngine.cpp \
    game/Game.cpp \
    items/WeaponsArmory.cpp \
    items/Weapon.cpp \
    items/Shotgun.cpp \
    items/RocketLauncher.cpp \
    items/MonsterBasicWeapon.cpp \
    items/MachineGun.cpp \
    items/Gun.cpp \
    items/ElmarMachineGun.cpp \
    menus/PauseMenu.cpp \
    menus/OptionsMenu.cpp \
    menus/MenuWaitForPlayers.cpp \
    menus/MenuMulti.cpp \
    menus/MenuJoin.cpp \
    menus/MenuHost.cpp \
    menus/MenuActionString.cpp \
    menus/MenuActionSelectMap.cpp \
    menus/MenuActionKeyconfig.cpp \
    menus/MenuActionInteger.cpp \
    menus/MenuActionClassic.cpp \
    menus/MenuAction.cpp \
    menus/Menu.cpp \
    menus/MainMenu.cpp \
    menus/ListMenuActions.cpp \
    menus/KeyconfigMenu.cpp \
    menus/ChoseLevelMenu.cpp \
    physic/MovingPlatform.cpp \
    physic/FallingPlatform.cpp \
    physic/CollisionsMatrix.cpp \
    physic/CollisionsManager.cpp \
    physic/ChainedPlatform.cpp \
    physic/BindablePlatform.cpp \
    players/PlayersManager.cpp \
    players/Player.cpp \
    sets/AnimatedSetsManager.cpp \
    sets/AnimatedSet.cpp \
    sets/AnimatedPhysicSet.cpp \
    sets/AnimatedNophysicSet.cpp \
    soil/stb_image_aug.c \
    soil/SOIL.c \
    soil/image_helper.c \
    soil/image_DXT.c \
    sound/SoundEngine.cpp \
    sound/Sound.cpp \
    sound/Sonorisable.cpp \
    sprites/SpritesManager.cpp \
    sprites/SpriteAnimTable.cpp \
    sprites/SpriteAnim.cpp \
    sprites/Sprite.cpp \
    util/Rect.cpp \
    util/RandomGenerator.cpp \
    util/globals.cpp \
    util/Constants.cpp \
    util/ArgAnalyser.cpp \
    util/Analyser.cpp \
	video/ressources/UniformSurfaceMap.cpp \
    video/TransitionScreen.cpp \
    video/Talks.cpp \
    video/SurfaceUniform.cpp \
    video/SurfaceText.cpp \
    video/SurfaceSelectionMenu.cpp \
    video/SurfaceFrame.cpp \
    video/SurfaceCompositeItem.cpp \
    video/SurfaceComposite.cpp \
    video/SurfaceBig.cpp \
    video/Surface.cpp \
    video/Statics.cpp \
    video/SpecialLetter.cpp \
    video/PicturesContainer.cpp \
    video/MainTitle.cpp \
    video/LifeBarPossessor.cpp \
    video/KeyMapSurfaceUnif.cpp \
    video/KeyMapSurfaceText.cpp \
    video/GraphicEngine.cpp \
    video/Dashboard.cpp \
    video/Camera.cpp \
    video/BigImage.cpp \
    video/AnimText.cpp \
	video/AnimTable.cpp \
	video/AnimPic.cpp \
	main.cpp \
    network/NetworkController.cpp \
    controllers/EventController.cpp \
    controllers/NetworkEventController.cpp \
    controllers/ItemEventController.cpp \
    controllers/PlayerEventController.cpp \
    controllers/NetworkItemEventController.cpp \
    controllers/NetworkPlayerEventController.cpp \
    controllers/ActionControlled.cpp \
    controllers/EventControlled.cpp \
    controllers/ControllerFactory.cpp \
    controllers/Controller.cpp \
    controllers/Controlled.cpp \
    actors/babar_states/BabarState.cpp \
    actors/babar_states/BabarStateNone.cpp \
    actors/babar_states/BabarStateRun.cpp \
    actors/babar_states/BabarStateJump.cpp \
    actors/babar_states/BabarStateDoubleJump.cpp \
    actors/babar_states/BabarStateCrouchNone.cpp \
    actors/babar_states/BabarStateCrouchWalking.cpp

HEADERS  += \
    actors/WalkingMonster.h \
    actors/Rocket.h \
    actors/RemoteBabar.h \
    actors/ProjectilesManager.h \
    actors/Projectile.h \
    actors/MonstersManager.h \
    actors/Monster.h \
    actors/FollowingWalkingMonster.h \
    actors/FollowingFlyingMonster.h \
    actors/FlyingMonster.h \
    actors/Explosion.h \
    actors/ElmarTile.h \
    actors/ChargingMonster.h \
    actors/BossElmar.h \
    actors/Boss.h \
    actors/Babar.h \
    actors/Actor.h \
    AI/AI.h \
    control/SfmlKeyConvertor.h \
    control/KeyboardConfig.h \
    control/Keyboard.h \
    control/InputString.h \
    control/EventKeyboard.h \
	controllers/ActionController.h \
	controllers/NetworkActionController.h \
	controllers/KeyboardActionController.h \
	controllers/MenuKeyboardActionController.h \
	controllers/PlayerKeyboardActionController.h \
	controllers/NetworkMenuActionController.h \
	controllers/NetworkPlayerActionController.h \
	controllers/NetworkRemotePlayerActionController.h \
	controllers/NetworkLocalPlayerActionController.h \
    events/Triggerable.h \
    events/Trigger.h \
    events/Stats.h \
    events/EventsManager.h \
    events/Event.h \
    game/StaticData.h \
    game/LevelsManager.h \
    game/GameInitializer.h \
    game/GameEngine.h \
    game/Game.h \
    items/WeaponsArmory.h \
    items/Weapon.h \
    items/Shotgun.h \
    items/RocketLauncher.h \
    items/MonsterBasicWeapon.h \
    items/MachineGun.h \
    items/Gun.h \
    items/ElmarMachineGun.h \
    menus/PauseMenu.h \
    menus/OptionsMenu.h \
    menus/MenuWaitForPlayers.h \
    menus/MenuMulti.h \
    menus/MenuJoin.h \
    menus/MenuHost.h \
    menus/MenuActionString.h \
    menus/MenuActionSelectMap.h \
    menus/MenuActionKeyconfig.h \
    menus/MenuActionInteger.h \
    menus/MenuActionClassic.h \
    menus/MenuAction.h \
    menus/Menu.h \
    menus/MainMenu.h \
    menus/ListMenuActions.h \
    menus/KeyconfigMenu.h \
    menus/ChoseLevelMenu.h \
    param/param_talks.h \
    param/param_menus.h \
    param/param_dashboard.h \
    physic/MovingPlatform.h \
    physic/FallingPlatform.h \
    physic/CollisionsMatrix.h \
    physic/CollisionsManager.h \
    physic/ChainedPlatform.h \
    physic/BindablePlatform.h \
    players/PlayersManager.h \
    players/Player.h \
    sets/AnimatedSetsManager.h \
    sets/AnimatedSet.h \
    sets/AnimatedPhysicSet.h \
    sets/AnimatedNophysicSet.h \
    soil/stbi_DDS_aug_c.h \
    soil/stbi_DDS_aug.h \
    soil/stb_image_aug.h \
    soil/SOIL.h \
    soil/image_helper.h \
    soil/image_DXT.h \
    sound/SoundEngine.h \
    sound/Sound.h \
    sound/Sonorisable.h \
    sound/SoundEngine.h \
    sound/Sound.h \
    sound/Sonorisable.h \
    sprites/SpritesManager.h \
    sprites/SpriteAnimTable.h \
    sprites/SpriteAnim.h \
    sprites/Sprite.h \
    util/utils.h \
    util/RessourcesMap.h \
    util/repertories.h \
    util/Rect.h \
    util/RandomGenerator.h \
    util/macros.h \
    util/lists.h \
    util/globals.h \
    util/enums.h \
    util/debug.h \
    util/Constants.h \
    util/ArgAnalyser.h \
    util/Analyser.h \
	video/ressources/UniformSurfaceMap.h \
	video/ressources/FontMap.h \
    video/TransitionScreen.h \
    video/Talks.h \
    video/SurfaceUniform.h \
    video/SurfaceText.h \
    video/SurfaceSelectionMenu.h \
    video/SurfaceFrame.h \
    video/SurfaceCompositeItem.h \
    video/SurfaceComposite.h \
    video/SurfaceBig.h \
    video/Surface.h \
    video/Statics.h \
    video/SpecialLetter.h \
    video/PicturesContainer.h \
    video/MainTitle.h \
    video/LifeBarPossessor.h \
    video/KeyMapSurfaceUnif.h \
    video/KeyMapSurfaceText.h \
    video/GraphicEngine.h \
    video/Displayable.h \
    video/Dashboard.h \
    video/Camera.h \
    video/BigImage.h \
    video/AnimText.h \
    video/AnimTable.h \
    video/AnimPic.h \
	video/Anim.h \
    network/NetworkController.h \
    controllers/EventController.h \
    controllers/NetworkEventController.h \
    controllers/ItemEventController.h \
    controllers/PlayerEventController.h \
    controllers/NetworkItemEventController.h \
    controllers/NetworkPlayerEventController.h \
    controllers/ActionControlled.h \
    controllers/EventControlled.h \
    controllers/ControllerFactory.h \
    controllers/Controller.h \
    controllers/Controlled.h \
    actors/babar_states/BabarState.h \
    actors/babar_states/BabarStateNone.h \
    actors/babar_states/BabarStateRun.h \
    actors/babar_states/BabarStateJump.h \
    actors/babar_states/BabarStateDoubleJump.h \
    actors/babar_states/BabarStateCrouchNone.h \
    actors/babar_states/BabarStateCrouchWalking.h

OTHER_FILES += \
    soil/stbi_DDS_aug_c.h.gch \
    soil/stbi_DDS_aug.h.gch \
    soil/stb_image_aug.h.gch \
    soil/SOIL.h.gch \
    soil/image_helper.h.gch \
    soil/image_DXT.h.gch
