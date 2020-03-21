#ifndef Dictionary_h
#define Dictionary_h

enum class ResourceName {
	Sheep = 1,
	Lumber = 2,
	Rock = 3,
    Wheat = 4
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
	RedLumber = 1,
	GreenSheep = 2,
	YellowHay = 3,
    GreyRock = 4,
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
