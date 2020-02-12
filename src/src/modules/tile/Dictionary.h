#ifndef Dictionary_h
#define Dictionary_h

enum class ResourceName {
    Lumber,
    Rock,
    Sheep,
    Wheat
};

enum class TileStatus {
    InHand,
    InDeck,
    OnBoard
};

enum ResourceLocation {
    topLeft = 0, topRight = 1, bottomLeft = 2, bottomRight = 3
};

enum class BuildingColorType {
    GreenSheep,
    GreyRock,
    RedLumber,
    YellowHay
};

enum class BuildingStatus {
    Normal,
    Flipped
};

enum class Connection {
    Up,
    Down,
    Right,
    Left
};

enum class VGSlotStatus {
    Empty, //int 0
    BuildingColorType //int 1
};


#endif /* Dictionary_h */
