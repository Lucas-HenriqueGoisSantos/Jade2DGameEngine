-- This is a Lua Global Variable
some_variable = 9 * 6

config = {

    fullscreen = false,

    resolution = {

        width = 800,
        height = 600
    }
}

entities = {

    tank = {

        tranform = {

            position = { x = 300, y = 200 },
            scale = { ... },
        },
        boxcollider = {
            ...
        },
        projectile_emitter = {

            angle = rand( 0, 360 ),
        }
    }
}