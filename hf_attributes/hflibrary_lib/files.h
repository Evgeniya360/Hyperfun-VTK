
#define fileNum 5
static int readfiles[fileNum] = {1,1,1,1,1};

typedef struct 
{
	double x;
	double y;
	double z;
	double fval;
} GRIDData;

//static double  Grid[dx][dy][dz];
static GRIDData* grData[fileNum];


static int dx[fileNum];
static int dy[fileNum];
static int dz[fileNum];

static double  stepx[fileNum];
static double  stepy[fileNum];
static double  stepz[fileNum];

static double originx[fileNum];
static double  originy[fileNum];
static double  originz[fileNum];

static GRIDData* grDataX[fileNum];
static GRIDData* grDataY[fileNum];
static GRIDData* grDataZ[fileNum];


static double * Xx2[fileNum];