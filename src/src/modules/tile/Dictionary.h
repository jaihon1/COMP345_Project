#ifndef Dictionary_h
#define Dictionary_h

enum class ResourceName {
    Lumber = 1,
	Sheep = 2,
	 Wheat = 3,
	Rock = 4
};

enum class ResourceName1 {
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
	topLeft = 0,
    topRight = 1,
    bottomLeft = 2,
    bottomRight = 3
};

enum class BuildingColorType {
    GreenSheep = 1,
    GreyRock = 2,
    RedLumber = 3,
    YellowHay = 4,
    None //initial value for the initialization of the empty VGMap - matches VGSlotStatus::Empty
};

enum class BuildingStatus {
    Normal = 0,
    Flipped = 1
};

enum class Connection {
    Up,
    Down,
    Right,
    Left
};

enum class VGSlotStatus {
    Empty, //int 0
    Taken, //int 1
    Unavailable //int 2 - any invalid slot (outside the actual map)
};


#endif /* Dictionary_h */
