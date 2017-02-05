#include "common/util.h"
#include "common/exception.h"

#include "io/block.h"
#include "io/console.h"
#include "io/inSystem.h"
#include "io/blockParser.h"
#include "io/inConstraints.h"

#include "fitting/fitter.h"

#include "configuration/constraints.h"
#include "configuration/configuration.h"

#include <chrono>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <tclap/CmdLine.h>

using namespace FieldFit;
using namespace std::chrono;

void ReadFilesFromList( const std::string &file, std::vector< std::string > &appList )
{
    std::ifstream stream;
    stream.open( file.c_str(), std::ios::in );
        
    if ( !stream.is_open() )
    {
        throw ArgException( "::", "ReadFilesFromList", "Unable to open file "+file );
    }
        
    std::string line = "";
    while ( getline ( stream, line ) )
    {
        line = Util::Trim( line );
        
        if ( line.size() > 0 )
        {
            //test for comment
            if ( line[0] == '#' )
            {
                continue;
            }
            
            appList.push_back( line );
        }
    }
}

int main(int argc, char** argv)
{
    std::vector< std::string > multiFiles;
    std::vector< std::string > fieldFiles;
    
    bool json = false;
    bool verbose = false;
    
    Console console;
    auto t0 = high_resolution_clock::now();
    
	try 
    {  
        const std::string blockDesc = "Block Description: ";
	    TCLAP::CmdLine cmd( blockDesc, ' ', "0.9" );
	        
	    TCLAP::SwitchArg verboseSwitch("v","verbose","Print verbose output", cmd, false);
        TCLAP::SwitchArg jsonSwitch("j","json","Format output as json", cmd, false);
       
        TCLAP::MultiArg<std::string> multiFileArg("f", "files", "File containing field-fit file names", false,"string" );
        TCLAP::UnlabeledMultiArg<std::string> multi( "fieldFiles", "Generic input for field-files containing blocks", false,"string" );
       
        cmd.add( multiFileArg );
        //make sure this is last
        cmd.add(  multi );
	    cmd.parse( argc, argv );
       
        multiFiles = multiFileArg.getValue();
        fieldFiles = multi.getValue();
       
        json = jsonSwitch.getValue();
        verbose = verboseSwitch.getValue();
	} 
    catch (TCLAP::ArgException &e)  // catch any exceptions
	{ 
        console.Error( Message( "::", "TCLAP::main", e.error() ) );
    }
    
    try 
    {
        // In a first step we grep all the lines from the multifiles
        for ( const std::string &f : multiFiles )
        {
            ReadFilesFromList(f,fieldFiles);
        }
        
        Configuration config;
        Constraints   constr;
        
        // Initiate reading of the field files
        BlockParser bp(fieldFiles);
        
        const Units units = ReadUnits( bp );
        
        ReadSystems( bp, units, config );
        ReadGrids( bp, units, config );
        ReadFields( bp, units, config );
        ReadEfields( bp, units, config );
        
        // parse constraints
        ReadSumConstraintSet( bp, units, constr );
        ReadSymConstraintSet( bp, units, constr );
        
        //clean up after reading
        bp.Clear();
        
        // start data generation
        for ( FieldFit::System *sys : config.GetSystems() )
        {
            if (sys)
            {
                sys->OnUpdate();
            }   
        }
        
        Fitter fitter; 
        fitter.Fit( console, config, constr, verbose );
    }
    catch (FieldFit::ArgException &e)  // catch any exceptions
	{ 
        console.Error( e.GenMessage() );
    }
    
    auto t1 = high_resolution_clock::now();
    std::cout << "Runtime (milliseconds): " << duration_cast<milliseconds>(t1 - t0).count() << std::endl;
    
    console.WritePlain(std::cout);
}