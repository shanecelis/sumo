/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.dev/sumo
// Copyright (C) 2001-2023 German Aerospace Center (DLR) and others.
// This program and the accompanying materials are made available under the
// terms of the Eclipse Public License 2.0 which is available at
// https://www.eclipse.org/legal/epl-2.0/
// This Source Code may also be made available under the following Secondary
// Licenses when the conditions for such availability set forth in the Eclipse
// Public License 2.0 are satisfied: GNU General Public License, version 2
// or later which is available at
// https://www.gnu.org/licenses/old-licenses/gpl-2.0-standalone.html
// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
/****************************************************************************/
/// @file    GNETagProperties.h
/// @author  Pablo Alvarez Lopez
/// @date    Jan 2020
///
// Abstract Base class for tag properties used in GNEAttributeCarrier
/****************************************************************************/
#pragma once
#include <config.h>


// ===========================================================================
// included modules
// ===========================================================================

#include <utils/gui/images/GUIIcons.h>
#include <netedit/GNEViewNetHelper.h>

#include "GNEAttributeProperties.h"


// ===========================================================================
// class definitions
// ===========================================================================

class GNETagProperties {

public:

    enum TagType {
        // basic types
        NETWORKELEMENT =    1 << 0,  // Network elements (Edges, Junctions, Lanes...)
        ADDITIONALELEMENT = 1 << 1,  // Additional elements (Bus Stops, Charging Stations, Detectors...)
        DEMANDELEMENT =     1 << 2,  // Demand elements (Routes, Vehicles, Trips...)
        DATAELEMENT =       1 << 3,  // Data elements (DataSets, Data Intervals, EdgeData...)
        // sub additional elements
        STOPPINGPLACE =     1 << 4,  // StoppingPlaces (BusStops, ChargingStations...)
        DETECTOR =          1 << 5,  // Detectors (E1, E2...)
        CALIBRATOR =        1 << 6,  // Calibrators
        SHAPE =             1 << 7,  // Shapes (Polygons and POIs)
        TAZELEMENT =        1 << 8,  // Traffic Assignment Zones
        WIRE =              1 << 9,  // Wire elements
        JUPEDSIM =          1 << 10, // JuPedSim elements
        // sub demand elements
        VTYPE =             1 << 11, // Vehicle types (vType and vTypeDistribution)
        VEHICLE =           1 << 12, // Vehicles (Vehicles, trips, flows...)
        ROUTE =             1 << 13, // Routes and embedded routes
        STOP =              1 << 14, // Stops
        WAYPOINT =          1 << 15, // Waypoints (note: All waypoints are also Stops)
        FLOW =              1 << 16, // Flows
        // persons
        PERSON =            1 << 17, // Persons (Persons and personFlows)
        PERSONPLAN =        1 << 18, // Person plans (Walks, rides, personTrips and stopPersons)
        PERSONTRIP =        1 << 19, // Person Trips
        WALK =              1 << 20, // Walks
        RIDE =              1 << 21, // Rides
        STOPPERSON =        1 << 22, // Person stops
        // containers
        CONTAINER =         1 << 23, // Containers (Containers and personFlows)
        CONTAINERPLAN =     1 << 24, // Container plans (tranship and transport)
        TRANSPORT =         1 << 25, // Transport
        TRANSHIP =          1 << 26, // Tranship
        STOPCONTAINER =     1 << 27, // Container stops
        // sub data elements
        GENERICDATA =       1 << 28, // Generic data (GNEEdgeData, GNELaneData...)
        MEANDATA =          1 << 29, // Mean datas
        // other
        SYMBOL =            1 << 30, // Symbol elements (VSSSymbols, RerouterSymbols...)
        INTERNALLANE =      1 << 31, // Internal Lane
    };

    enum TagProperty {
        NOTDRAWABLE =               1 << 0,     // Element cannot be drawn in view
        CLOSESHAPE =                1 << 1,     // Element can close their shape
        GEOSHAPE =                  1 << 2,     // Element's shape acn be defined using a GEO Shape
        DIALOG =                    1 << 3,     // Element can be edited using a dialog (GNECalibratorDialog, GNERerouterDialog...)
        CHILD =                     1 << 4,     // Element is child of another element and will be written in XML without id (Example: E3Entry -> E3Detector...)
        REPARENT =                  1 << 5,     // Element can be reparent
        NOTSELECTABLE =             1 << 6,     // Element cannot be selected
        MASKSTARTENDPOS =           1 << 7,     // Element mask attributes StartPos and EndPos as "length" (Only used in the appropiate GNEFrame)
        NOPARAMETERS =              1 << 8,     // Element doesn't accept parameters "key1=value1|key2=value2|...|keyN=valueN" (by default all tags supports parameters)
        RTREE =                     1 << 9,     // Element is placed in RTREE
        CENTERAFTERCREATION =       1 << 10,    // Camera is moved after element creation
        REQUIRE_PROJ =              1 << 11,    // Element require a geo-projection defined in network
        VCLASS_ICON =               1 << 12,    // Element returns icon depending of their vClass
        // exclusive of vehicles
        OVER_ROUTE =                1 << 13,    // Vehicle Element is placed over route
        OVER_EMBEDDED_ROUTE =       1 << 14,    // Vehicle Element has an embedded route
        OVER_FROMTO_EDGES =         1 << 15,    // Vehicle Element is placed over a from-to edges
        OVER_FROMTO_JUNCTIONS =     1 << 16,    // Vehicle Element is placed over a from-to junctions
        OVER_FROMTO_TAZS =          1 << 17,    // Vehicle Element is placed over a from-to TAZs
    };

    /// @brief default constructor
    GNETagProperties();

    /// @brief parameter constructor
    GNETagProperties(const SumoXMLTag tag, const int tagType, const int tagProperty, const GUIIcon icon, const SumoXMLTag XMLTag,
                     const std::string tooltip, std::vector<SumoXMLTag> parentTags = {},
                     const unsigned int backgroundColor = FXRGBA(255, 255, 255, 255), const std::string fieldString = "");

    /// @brief destructor
    ~GNETagProperties();

    /// @brief get Tag vinculated with this attribute Property
    SumoXMLTag getTag() const;

    /// @brief get supermode associated with this tag
    Supermode getSupermode() const;

    /// @brief get Tag vinculated with this attribute Property in String Format (used to avoid multiple calls to toString(...)
    const std::string& getTagStr() const;

    /// @brief check Tag integrity (this include all their attributes)
    void checkTagIntegrity() const;

    /// @brief add attribute (duplicated attributed aren't allowed)
    void addAttribute(const GNEAttributeProperties& attributeProperty);

    /// @brief get field string (by default tag in string format)
    const std::string& getFieldString() const;

    /// @brief get background color
    unsigned int getBackGroundColor() const;

    /// @brief get attribute (throw error if doesn't exist)
    const GNEAttributeProperties& getAttributeProperties(SumoXMLAttr attr) const;

    /// @brief get begin of attribute values (used for iterate)
    std::vector<GNEAttributeProperties>::const_iterator begin() const;

    /// @brief get end of attribute values (used for iterate)
    std::vector<GNEAttributeProperties>::const_iterator end() const;

    /// @brief get attribute value
    const GNEAttributeProperties& at(int index) const;

    /// @brief get number of attributes
    int getNumberOfAttributes() const;

    /// @brief return the default value of the attribute of an element
    const std::string& getDefaultValue(SumoXMLAttr attr) const;

    /// @brief get GUI icon associated to this Tag
    GUIIcon getGUIIcon() const;

    /// @brief get XML tag
    SumoXMLTag getXMLTag() const;

    /// @brief get parent tags
    const std::vector<SumoXMLTag>& getParentTags() const;

    /// @brief check if current TagProperties owns the attribute "attr"
    bool hasAttribute(SumoXMLAttr attr) const;

    /// @brief return true if tag correspond to a network element
    bool isNetworkElement() const;

    /// @brief return true if tag correspond to an additional element (note: this include TAZ, shapes and wires)
    bool isAdditionalElement() const;

    /// @brief return true if tag correspond to a pure additional element
    bool isAdditionalPureElement() const;

    /// @brief return true if tag correspond to a demand element
    bool isDemandElement() const;

    /// @brief return true if tag correspond to a data element
    bool isDataElement() const;

    /// @brief return true if tag correspond to a detector (Only used to group all stoppingPlaces in the output XML)
    bool isStoppingPlace() const;

    /// @brief return true if tag correspond to a shape (Only used to group all detectors in the XML)
    bool isDetector() const;

    /// @brief return true if tag correspond to a calibrator (Only used to group all detectors in the XML)
    bool isCalibrator() const;

    /// @brief return true if tag correspond to a shape
    bool isShapeElement() const;

    /// @brief return true if tag correspond to a TAZ element
    bool isTAZElement() const;

    /// @brief return true if tag correspond to a Wire element
    bool isWireElement() const;

    /// @brief return true if tag correspond to a JuPedSim element
    bool isJuPedSimElement() const;

    /// @brief return true if tag correspond to a vehicle/person/container type element
    bool isType() const;

    /// @brief return true if tag correspond to a vehicle element
    bool isVehicle() const;

    /// @brief return true if tag correspond to a route element
    bool isRoute() const;

    /// @brief return true if tag correspond to a stop element
    bool isStop() const;

    /// @brief return true if tag correspond to a waypoint element
    bool isWaypoint() const;

    /// @brief return true if tag correspond to a flow element
    bool isFlow() const;

    /// @brief return true if tag correspond to a person element
    bool isPerson() const;

    /// @brief return true if tag correspond to a person plan
    bool isPersonPlan() const;

    /// @brief return true if tag correspond to a person trip
    bool isPersonTrip() const;

    /// @brief return true if tag correspond to a walk element
    bool isWalk() const;

    /// @brief return true if tag correspond to a ride element
    bool isRide() const;

    /// @brief return true if tag correspond to a person stop element
    bool isStopPerson() const;

    /// @brief return true if tag correspond to a container element
    bool isContainer() const;

    /// @brief return true if tag correspond to a container plan
    bool isContainerPlan() const;

    /// @brief return true if tag correspond to a transport
    bool isTransportPlan() const;

    /// @brief return true if tag correspond to a tranship
    bool isTranshipPlan() const;

    /// @brief return true if tag correspond to a container stop element
    bool isStopContainer() const;

    /// @brief return true if tag correspond to a generic data element
    bool isGenericData() const;

    /// @brief return true if tag correspond to a mean data element
    bool isMeanData() const;

    /// @brief return true if tag correspond to an element child of another element (Example: E3->Entry/Exit)
    bool isChild() const;

    /// @brief return true if tag correspond to a symbol element
    bool isSymbol() const;

    /// @brief return true if tag correspond to an internal lane
    bool isInternalLane() const;

    /// @brief return true if tag correspond to a drawable element
    bool isDrawable() const;

    /// @brief return true if tag correspond to a selectable element
    bool isSelectable() const;

    /// @brief return true if tag correspond to an element that can close their shape
    bool canCloseShape() const;

    /// @brief return true if tag correspond to an element that can use a geo shape
    bool hasGEOShape() const;

    /// @brief return true if tag correspond to an element that can be edited using a dialog
    bool hasDialog() const;

    /// @brief return true if Tag correspond to an element that supports parameters "key1=value1|key2=value2|...|keyN=valueN"
    bool hasParameters() const;

    /// @brief return true if Tag correspond to an element that has to be placed in RTREE
    bool isPlacedInRTree() const;

    /// @brief return true if tag correspond to an element that can be reparent
    bool canBeReparent() const;

    /// @brief return true if tag correspond to an element that can mask the attributes "start" and "end" position as attribute "length"
    bool canMaskStartEndPos() const;

    /// @brief return true if tag correspond to an element that center camera after creation
    bool canCenterCameraAfterCreation() const;

    /// @brief return true if tag correspond to an element that requires a geo projection
    bool requireProj() const;

    /// @brief return true if tag correspond to an element that has vClass icons
    bool vClassIcon() const;

    /// @brief return true if tag correspond to a vehicle placed over a route
    bool overRoute() const;

    /// @brief return true if tag correspond to a vehicle placed over an embedded route
    bool overEmbeddedRoute() const;

    /// @brief return true if tag correspond to a vehicle placed over from-to edges
    bool overFromToEdges() const;

    /// @brief return true if tag correspond to a vehicle placed over from-to junctions
    bool overFromToJunctions() const;

    /// @brief return true if tag correspond to a vehicle placed over from-to TAZs
    bool overFromToTAZs() const;

private:
    /// @brief Sumo XML Tag vinculated wit this tag Property
    SumoXMLTag myTag;

    /// @brief Sumo XML Tag vinculated wit this tag Property in String format
    std::string myTagStr;

    /// @brief Attribute Type
    int myTagType;

    /// @brief Attribute properties
    int myTagProperty;

    /// @brief vector with the attribute values vinculated with this Tag
    std::vector<GNEAttributeProperties> myAttributeProperties;

    /// @brief icon associated to this Tag
    GUIIcon myIcon;

    /// @brief Tag written in XML and used in GNENetHelper::AttributeCarriers
    SumoXMLTag myXMLTag;

    /// @brief tooltip text
    std::string myTooltipText;

    /// @brief vector with master tags (used by child elements)
    std::vector<SumoXMLTag> myParentTags;

    /// @brief field string
    std::string myFieldString;

    /// @brief background color (used in labels and textFields, by default white)
    unsigned int myBackgroundColor;
};

/****************************************************************************/

