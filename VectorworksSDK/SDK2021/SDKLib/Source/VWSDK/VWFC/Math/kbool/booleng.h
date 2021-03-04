#pragma once


// from http://www.xs4all.nl/~kholwerd/download/download.html

#include "valuesvc.h"

#define KBOOL_VERSION "1.8"

#define KBOOL_DEBUG 0

// results could be incorrect when coordinates of processed points are too big.
const double KBOOL_MAX_COORD_VAL = 400000000.0;



//! errors in the boolean algorithm will be thrown using this class
class Bool_Engine_Error
{
public:
	Bool_Engine_Error(const char* message, const char* header=0, Sint32 degree = 9, Sint32 fatal = 0);
	Bool_Engine_Error(const Bool_Engine_Error& a);
	~Bool_Engine_Error();
};


enum kbEdgeType 
{ 
	KB_OUTSIDE_EDGE, /*!< edge of the outside contour of a polygon */
	KB_INSIDE_EDGE,  /*!< edge of the inside hole a polygon */
	KB_FALSE_EDGE    /*!< edge to connect holes into polygons */
} ;

enum kbGroupType 
{ 
	GROUP_A, /*!< to set Group A for polygons */
	GROUP_B  /*!< to set Group A for polygons */
};

enum BOOL_OP 
{ 
	BOOL_OR, /*!< boolean OR operation */
	BOOL_AND, /*!< boolean AND operation */
	BOOL_EXOR, /*!< boolean EX_OR operation */
	BOOL_A_SUB_B, /*!< boolean Group A - Group B operation */
	BOOL_B_SUB_A, /*!< boolean Group B - Group A operation */
	BOOL_CORRECTION, /*!< polygon correction/offset operation */
	BOOL_SMOOTHEN, /*!< smooth operation */
	BOOL_MAKERING /*!< create a ring on all polygons */
};

class GraphList;
class Graph;
class KBoolLink;
class Node;

//! boolean engine to perform operation on two sets of polygons.
/*
First the engine needs to be filled with polygons.
The first operand in the operation is called group A polygons, the second group B.
The boolean operation ( BOOL_OR, BOOL_AND, BOOL_EXOR, BOOL_A_SUB_B, BOOL_B_SUB_A )
are based on the two sets of polygons in group A and B.
The other operation on group A only.

At the end of the operation the resulting polygons can be extracted.
*/
class Bool_Engine {

public:

	//! constructor    
					Bool_Engine();

	//! destructor   
	virtual			~Bool_Engine();

	const char*			GetVersion() { return KBOOL_VERSION; }

	//! if more then one Boolean engines are instantiated at the same time,
	/*! one needs to activate the one in use before using it.
	This sets a global pointer to the current active boolean engine used by other classes
	in the algorithm, to get settings from the active enigine for the algorithm.
	*/     
	void			Activate();

	//! reports progress of algorithm.
	virtual void	SetState( const char* = 0 );

	//! called at an internal error.
	virtual void	error(const char *text, const char *title);

	//! called at an internal generated possible error.
	virtual void	info(const char *text, const char *title);

	bool			Do_Operation(BOOL_OP operation);


	//! distance within which points and lines will be snapped towards lines and other points
	/*
	The algorithm takes into account gaps and inaccuracies caused by rounding to integer coordinates
	in the original data.
	Imagine two rectangles one with a side ( 0,0 ) ( 2.0, 17.0 ) 
	and the other has a side ( 0,0 ) ( 1.0, 8.5 )
	If for some reason those coordinates where round to ( 0,0 ) ( 2, 17 ) ( 0,0 ) ( 1, 9 ),
	there will be clearly a gap or overlap that was not intended.
	Even without rounding this effect takes place since there is always a minimum significant bit
	also when using doubles.

	If the user used as minimum accuracy 0.001, you need to choose Marge > 0.001
	The boolean engine scales up the input data with GetDGrid() * GetGrid() and rounds the result to
	integer, So (assuming GRID = 100 DGRID = 1000)  a vertex of 123.001 in the user data will
	become 12300100 internal.
	At the end of the algorithm the internal vertexes are scaled down again with GetDGrid() * GetGrid(),
	so 12300103 becomes 123.00103 eventually.
	So indeed the minimum accuracy might increase, you are free to round again if needed.
	*/
	void			SetMarge(double marge);
	double			GetMarge();

	//! input points are scaled up with GetDGrid() * GetGrid()
	/*
	Grid makes sure that the integer data used within the algorithm has room for extra intersections
	smaller than the smallest number within the input data.
	The input data scaled up with DGrid is related to the accuracy the user has in his input data.
	Another scaling with Grid is applied on top of it to create space in the integer number for 
	even smaller numbers. 
	*/
	void			SetGrid(B_INT grid);  

	//! See SetGrid
	B_INT			GetGrid();

	//! input points are scaled up with GetDGrid() * GetGrid()
	/*
	The input data scaled up with DGrid is related to the accuracy the user has in his input data.
	User data with a minimum accuracy of 0.001, means set the DGrid to 1000.
	The input data may contain data with a minimum accuracy much smaller, but by setting the DGrid
	everything smaller than 1/DGrid is rounded.

	DGRID is only meant to make fractional parts of input data which can be
	doubles, part of the integers used in vertexes within the boolean algorithm.
	And therefore DGRID bigger than 1 is not usefull, you would only loose accuracy.
	Within the algorithm all input data is multiplied with DGRID, and the result
	is rounded to an integer. 
	*/
	void			SetDGrid(double dgrid);

	//! See SetDGrid
	double			GetDGrid();

	//! When doing a correction operation ( also known as process offset )
	//! this defines the detail in the rounded corners.
	/*
	Depending on the round factor the corners of the polygon may be rounding within the correction
	algorithm. The detail within this rounded corner is set here.
	It defines the deviation the generated segments in arc like polygon may have towards the ideal
	rounded corner using a perfect arc.
	*/
	void			SetCorrectionAber(double aber);

	//! see SetCorrectionAber
	double			GetCorrectionAber();

	//! When doing a correction operation ( also known as process offset )
	//! this defines the amount of correction.
	/*
	The correction algorithm can apply positive and negative offset to polygons.
	It takes into account closed in areas within a polygon, caused by overlapping/selfintersecting
	polygons. So holes form that way are corrected proberly, but the overlapping parts itself
	are left alone. An often used trick to present polygons with holes by linking to the outside
	boundary, is therefore also handled properly.
	The algoritm first does a boolean OR operation on the polygon, and seperates holes and
	outside contours.
	After this it creates a ring shapes on the above holes and outside contours.
	This ring shape is added or subtracted from the holes and outside contours.
	The result is the corrected polygon.
	If the correction factor is > 0, the outside contours will become larger, while the hole contours
	will become smaller.
	*/
	void			SetCorrectionFactor(double aber);

	//! see SetCorrectionFactor
	double			GetCorrectionFactor();

	//! used within the smooth algorithm to define how much the smoothed curve may deviate
	//! from the original.
	void			SetSmoothAber(double aber);

	//! see SetSmoothAber
	double			GetSmoothAber();

	//! segments of this size will be left alone in the smooth algorithm.
	void			SetMaxlinemerge(double maxline);

	//! see SetMaxlinemerge
	double			GetMaxlinemerge();

	//! Polygon maye be fille in diffrent way (alternate and winding rule).
	//! This here defines which method will be assumed within the algorithm.
	void			SetWindingRule(bool rule);

	//! see SetWindingRule
	bool			GetWindingRule();

	//! the smallest accuracy used within the algorithm for comparing two real numbers.
	double			GetAccur();

	//! Used with in correction/offset algorithm.
	/*
	When the polygon contains sharp angles ( < 90 ), after a positive correction the
	extended parrallel constructed offset lines may leed to extreme offsets on the angles.
	The length of the crossing generated by the parrallel constructed offset lines
	towards the original point in the polygon is compared to the offset which needs to be applied.
	The Roundfactor then decides if this corner will be rounded.
	A Roundfactor of 1 means that the resulting offset will not be bigger then the correction factor
	set in the algorithm. Meaning even straight 90 degrees corners will be rounded.
	A Roundfactor of > sqrt(2) is where 90 corners will be left alone, and smaller corners will be rounded.
	*/
	void			SetRoundfactor(double roundfac);

	//! see SetRoundfactor
	double			GetRoundfactor();

	// the following are only be used within the algorithm,
	// since they are scaled with m_DGRID

	//! only used internal.
	void			SetInternalMarge( B_INT marge );
	//! only used internal.
	B_INT			GetInternalMarge();

	//! only used internal.
	double			GetInternalCorrectionAber();

	//! only used internal.
	double			GetInternalCorrectionFactor();

	//! only used internal.
	double			GetInternalSmoothAber();

	//! only used internal.
	B_INT			GetInternalMaxlinemerge();

	//!lof file will be created when set True
	void			SetLog( bool OnOff ); 

	// methods used to add polygons to the eng using points

	//! Start adding a polygon to the engine
	/*
	The boolean operation work on two groups of polygons ( group A or B ),
	other algorithms are only using group A.

	You add polygons like this to the engine.

	// foreach point in a polygon ...
	if (booleng->StartPolygonAdd(GROUP_A))
	{
	booleng->AddPoint(100,100);
	booleng->AddPoint(-100,100); 
	booleng->AddPoint(-100,-100); 
	booleng->AddPoint(100,-100); 
	}
	booleng->EndPolygonAdd(); 

	\param A_or_B defines if the new polygon will be of group A or B
	*/
	bool			StartPolygonAdd(kbGroupType A_or_B);

	//! see StartPolygonAdd
	bool			AddPoint(double x, double y);

	//! see StartPolygonAdd
	bool			EndPolygonAdd();

	// methods used to extract polygons from the eng by getting its points

	//Use after StartPolygonGet()
	Sint32				GetNumPointsInPolygon() { return m_numPtsInPolygon ; }

	//! get resulting polygons at end of an operation
	/*!
	// foreach resultant polygon in the booleng ...
	while ( booleng->StartPolygonGet() )
	{
	// foreach point in the polygon
	while ( booleng->PolygonHasMorePoints() )
	{
	fprintf(stdout,"x = %f\t", booleng->GetPolygonXPoint());
	fprintf(stdout,"y = %f\n", booleng->GetPolygonYPoint());
	}
	booleng->EndPolygonGet();
	}
	*/
	bool			StartPolygonGet(); 

	//! see StartPolygonGet
	/*!
	This iterates through the first graph in the graphlist.
	Setting the current Node properly by following the links in the graph
	through its nodes. 
	*/
	bool			PolygonHasMorePoints(); 

	//! see StartPolygonGet
	double			GetPolygonXPoint(); 

	//! see StartPolygonGet
	double			GetPolygonYPoint(); 

	//! in the resulting polygons this tells if the current polygon segment is one
	//! used to link holes into the outer contour of the polygon
	bool			GetHoleConnectionSegment();

	//! in the resulting polygons this tells if the current polygon segment is part
	//! of a hole within a polygon.
	bool			GetHoleSegment();

	//! an other way to get the type of segment.
	kbEdgeType		GetPolygonPointEdgeType();

	//! see StartPolygonGet()
	/*!
	Removes a graph from the graphlist.
	Called after an extraction of an output polygon was done.
	*/
	void			EndPolygonGet(); 

private:

	//! contains polygons in graph form
	GraphList*	m_graphlist;

	double			m_MARGE;
	B_INT			m_GRID;
	double			m_DGRID;
	double			m_CORRECTIONABER;
	double			m_CORRECTIONFACTOR;
	double			m_SMOOTHABER;
	double			m_MAXLINEMERGE;
	bool			m_WINDINGRULE;
	double			m_ACCUR;
	double			m_ROUNDFACTOR;

	//! used in the StartPolygonAdd, AddPt, EndPolygonAdd sequence
	Graph*			m_GraphToAdd;
	//! used in the StartPolygonAdd, AddPt, EndPolygonAdd sequence
	Node*			m_lastNodeToAdd;
	//! used in the StartPolygonAdd, AddPt, EndPolygonAdd sequence
	Node*			m_firstNodeToAdd;

	//! the current group type ( group A or B )
	kbGroupType		m_groupType;

	//! used in extracting the points from the resultant polygons
	Graph*			m_getGraph;
	//! used in extracting the points from the resultant polygons
	KBoolLink*		m_getLink;
	//! used in extracting the points from the resultant polygons
	Node*			m_getNode;
	//! used in extracting the points from the resultant polygons
	double			m_PolygonXPoint;
	//! used in extracting the points from the resultant polygons
	double			m_PolygonYPoint;
	//! used in extracting the points from the resultant polygons
	Sint32				m_numPtsInPolygon;
	//! used in extracting the points from the resultant polygons
	Sint32				m_numNodesVisited;

};

extern Bool_Engine *ACTIVE_BoolEng;

