#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

#include "includes/format_cout.h"

/**
 * LoginManager
 *
 * The login manager class enables a login routine to read and write
 * files containing usernames and passwords
 */
class LoginManager
{
 public:

    LoginManager()
    {
      /** Deny access initially */
      accessGranted = 0;
    }
    /**
     * login()
     *
     * Runs the login routine
     */
    void login()
    {
        cout << "Please enter your " << bold_on << "email address" << bold_off << ".\ne -> ";
        cin >> userNameAttempt;

        int usrID = checkFile( userNameAttempt, "users.dat" );
        if( usrID != 0 )
        {
            cout << "p -> ";
            cin >> passwordAttempt;

            int pwdID = checkFile( passwordAttempt, "pswds.dat" );
            if ( usrID == pwdID )
            {
                cout << "\nSuccessfully logged in.\n" << endl;
                login();

            }
            else
            {
                cout << "\nYou've entered an incorrect password.\nPlease try again.\n" << endl;
                login();
            }
        }
        else
        {
            cout << "\nSorry, that email could not be found.\nAre you sure you typed it correctly?\n" << endl;
            login();
        }
    }

    /**
     * addUser()
     *  This function adds new user information to the user.dat and pswd.dat files
     *  -- username
     *     Interactively specify an email address for the login
     *  -- password
     *     Interactively specify a password for the login
     */
    void addUser( const string username, const string password )
    {
        if ( checkFile( username, "users.dat" ) != 0 )
        {
            cout << "That username is not availble." << endl;
            return;
        }

        int id = 1 + getLastID();
        saveFile( username, "users.dat", id );
        saveFile( password, "pswds.dat", id );
    }

    /**
     * getLastID()
     *  Get the last ID while checking against provided login
     */
    int getLastID()
    {
        fstream file;
        file.open("users.dat", ios::in );
        file.seekg( 0, ios::end );

        if ( file.tellg() == -1)
            return 0;

        string s;

        for ( int i = -1; s.find( "#" ) == string::npos; i-- )
        {
            file.seekg( i, ios::end );
            file >> s;
        }

        file.close();
        s.erase( 0, 4 );

        int id;
        istringstream( s ) >> id;

        return id;
    }

    /**
     * checkFile()
     *   Checks provided login information against the user.dat and pswd.dat files
     * -- attempt
     *    The attempted login (private)
     * -- p_filename
     *    The name of the file to check against
     */
    int checkFile( string attempt, const char* p_fileName )
    {
        string line;
        fstream file;

        string currentChar;
        long long eChar;

        file.open( p_fileName, ios::in );

        while( 1 )
        {
            file >> currentChar;
            if ( currentChar.find( "#ID:" ) != string::npos )
            {
                if ( attempt == line )
                {
                    file.close();
                    currentChar.erase( 0, 4 );
                    int id;
                    istringstream( currentChar ) >> id;
                    return id;
                }

                else
                {
                    line.erase( line.begin(), line.end() );
                }
            }

            else
            {
                istringstream( currentChar ) >> eChar;
                line += ( char )decrypt( eChar );
                currentChar = "";
            }

            if ( file.peek() == EOF )
            {
                file.close();
                return 0;
            }
        }
    }

    /**
     * saveFile()
     *   Saves the encrypted file
     * -- p_line
     *    Line to check
     * -- p_fileName
     *    File to save
     * -- id
     *    ID of the provided login
     */
    void saveFile( string p_line, const char* p_fileName, const int& id )
    {
        fstream file;
        file.open( p_fileName, ios::app );
        file.seekg( 0, ios::end );

        if ( file.tellg() != 0 )
            file << "\n";

        file.seekg( 0, ios::beg );

        for ( long unsigned int i = 0; i < p_line.length(); i++ )
        {
            file << encrypt( p_line[i] );
            file << "\n";
        }

        file << "#ID:" << id;
        file.close();
    }

private:
    string userNameAttempt;
    string passwordAttempt;
    bool accessGranted;
    /** Encryption function */
    long long encrypt( int p_letter )
    {
        return powf( p_letter, 5 ) * 4 - 14;
    }
    /** Decryption (reverse of encryption) */
    int decrypt( long long p_letter )
    {
        return powf( ( p_letter + 14 ) / 4, 1/5.f );
    }
};

/**
 * main()
 *   Entrypoint for the login routine
 */
int main()
{
    LoginManager app;
    //app.addUser( "email@host.com", "password" );
    app.login();
    cin.get();
}
