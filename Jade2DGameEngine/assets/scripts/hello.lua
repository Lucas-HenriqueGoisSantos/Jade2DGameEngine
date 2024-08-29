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

    i = n;
    result = 1;

    while i >= 1 do
        result = result * i;
        i = i - 1;
    end

    print( result );
end

factorial( 5 )
factorial( 7 )