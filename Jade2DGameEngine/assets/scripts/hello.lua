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

function factorial( n )

    if n == 1 then
        return 1
    end

    return n * factorial( n-1 )
end

print( "The cube of the number 3 is equal to".. cube( 3 ) )