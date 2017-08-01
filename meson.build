project('PACMAN', 'cpp')
sfml_graphics_dep = dependency('sfml-graphics')
src = ['main.cpp', 'director.cpp',
       'util/resources.cpp',
       'scenes/scenetransition.cpp',
       'scenes/startscene.cpp',
       'scenes/gamescene.cpp',
       'scenes/levelcompletescene.cpp',
       'game/game.cpp',
       'game/maze.cpp',
       'game/cell.cpp',
       'game/hero.cpp',
       'game/monster.cpp',
       'game/levels.cpp',
       'game/playerview.cpp',
      ]
executable('pacman', src, dependencies: sfml_graphics_dep)
