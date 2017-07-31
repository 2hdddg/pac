project('PACMAN', 'cpp')
sfml_graphics_dep = dependency('sfml-graphics')
src = ['main.cpp', 'director.cpp',
       'scenes/start/startscene.cpp',
       'scenes/game/gamescene.cpp',
       'game/maze.cpp',
       'game/cell.cpp',
       'game/hero.cpp',
      ]
executable('pacman', src, dependencies: sfml_graphics_dep)
