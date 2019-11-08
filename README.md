# nodemcu-minikame
This is the selfmade source-code for the Mini-Kame quadruped robot made by Javier Isabel within https://www.thingiverse.com/thing:1265766

# Status
See this code as a prototype, because it is not cleaned up at the moment.

# What's in

## Onboard website with command-list and documentation

Access it via http://minikame.local/

## URL-commands

See http://minikame.local/ for a list of commands.

## Over the air (OTA) firmware updates

Allows updating the firmware without an USB-connection.

See the platformio.ini for the connection details.

# What's not (TODO-list)

1. clean code
	- remove unnecessary comments
	- more comments with code-documentation
	- move the code from header-files (.h) into code-files (.cpp)
2. list of commands
	- lets send a list of commands to the robot to run
	- needs rethinking the behavior-pattern
3. schematics of assembly
	- add some schematics of assembly to allow others rebuilding it easily
	- add a list of the parts needed to assemble a new robot (e.g. 8x SG90, screws, nuts, loctite 243, nodemcu, ...)
	- add suggestions to improve the assembly (e.g. don't use screws and nuts, but use pivot pins with split pins)
4. smartphone app
	- remove the pre-programmed / static behaviors on the bot
	- program the behaviors to a smartphone app
	- allow controlling the bot via a smartphone app
	- should be kids-friendly to allow education
	- allow recording the moves to define new behaviors

# License
GPLv3 - https://www.gnu.org/licenses/gpl-3.0.en.html
