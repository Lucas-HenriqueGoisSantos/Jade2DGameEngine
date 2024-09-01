-- Define a table with the values of the first level
Level = {

    ----------------------------------------------------
    -- Table to define the list of assets
    ----------------------------------------------------
    assets = {

        [0] =
        { type = "texture", id = "tilemap-texture", file = "./assets/tilemaps/jungle.png" },
        { type = "texture", id = "chopper-texture", file = "./assets/images/chopper-spritesheet.png" },
        { type = "texture", id = "tank-texture",    file = "./assets/images/tank-tiger-up.png" },
        { type = "texture", id = "truck-texture",   file = "./assets/images/truck-ford-right.png" },
        { type = "texture", id = "bullet-texture",  file = "./assets/images/bullet.png" },
        { type = "texture", id = "tree-texture",    file = "./assets/images/tree.png" },
        { type = "font"   , id = "pico8-font-5",    file = "./assets/fonts/pico8.ttf",    font_size = 5 },
        { type = "font"   , id = "pico8-font-10",   file = "./assets/fonts/pico8.ttf",    font_size = 10 },
        { type = "font"   , id = "charriot-font-20", file = "./assets/fonts/charriot.ttf", font_size = 20 },
        --ERR: [31-Aug-2024 23:31:12]: Error loading the Lua script: ./assets/scripts/Level1.lua:16: '}' expected near 'file'
    },

    ----------------------------------------------------
    -- table to define the map config variables
    ----------------------------------------------------
    tilemap = {

        map_file = "./assets/tilemaps/jungle.map",
        texture_asset_id = "tilemap-texture",
        num_rows = 20,
        num_cols = 25,
        tile_size = 32,
        scale = 3.0
    },

    ----------------------------------------------------
    -- table to define entities and their components
    ----------------------------------------------------
    entities = {

        [0] =
        {

            -- Player
            tag = "player",
            components = {

                transform = {

                    position = { x = 360.0, y = 165.0 },
                    scale = { x = 1.5, y = 1.5 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {

                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {

                    texture_asset_id = "chopper-texture",
                    width = 32,
                    height = 32,
                    z_index = 4,
                    fixed = false,
                    src_rect_x = 0,
                    src_rect_y = 0
                },
                animation = {

                    num_frames = 2,
                    speed_rate = 10 -- fps
                },
                boxcollider = {

                    width = 32,
                    height = 25,
                    offset = { x = 0, y = 5 }
                },
                health = {

                    health_percentage = 100
                },
                projectile_emitter = {

                    projectile_velocity = { x = 200, y = 200 },
                    projectile_duration = 10, -- seconds
                    repeat_frequency = 0, -- seconds
                    hit_percentage_damage = 10,
                    friendly = true
                },
                keyboard_controller = {

                    up_velocity = { x = 0, y = -50 },
                    right_velocity = { x = 50, y = 0 },
                    down_velocity = { x = 0, y = 50 },
                    left_velocity = { x = -50, y = 0 }
                },
                camera_follow = {

                    follow = true
                }
            }
        },
        {

            -- Tank
            group = "enemies",
            components = {

                transform = {

                    position = { x = 750.0, y = 750.0 },
                    scale = { x = 1.5, y = 1.5 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {

                    velocity = { x = 20.0, y = 0.0 }
                },
                sprite = {

                    texture_asset_id = "tank-texture",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
                boxcollider = {

                    width = 25,
                    height = 18,
                    offset = { x = 0, y = 7 }
                },
                health = {

                    health_percentage = 100
                },
                projectile_emitter = {

                    projectile_velocity = { x = 100, y = 0 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 20,
                    friendly = false
                }
            }
        },
        {

            -- Truck
            group = "enemies",
            components = {

                transform = {

                    position = { x = 180.0, y = 750.0 },
                    scale = { x = 1.5, y = 1.5 },
                    rotation = 0.0, -- degrees
                },
                sprite = {

                    texture_asset_id = "truck-texture",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
                boxcollider = {

                    width = 20,
                    height = 20,
                    offset = { x = 5, y = 5 }
                },
                health = {

                    health_percentage = 100
                }
            }
        },
        {

            --TreeA
            group = "obstacles",
            components = {

                transform = {

                    position = { x = 900.0, y = 742.5 },
                    scale = { x = 1.5, y = 1.5 },
                    rotation = 0.0
                },
                sprite = {

                    texture_asset_id = "tree-texture",
                    width = 16,
                    height = 32,
                    z_index = 2
                },
                boxcollider = {

                    width = 16,
                    height = 32
                }
            }
        },
        {

            --TreeB
            group = "obstacles",
            components = {

                transform = {

                    position = { x = 600.0, y = 742.5 },
                    scale = { x = 1.5, y = 1.5 },
                    rotation = 0.0
                },
                sprite = {

                    texture_asset_id = "tree-texture",
                    width = 16,
                    height = 32,
                    z_index = 2
                },
                boxcollider = {

                    width = 16,
                    height = 32
                }
            }
        }
    }
}