#!/usr/bin/env python

import os
import sys
from PyQt4 import QtCore, QtGui

#-------------------------------------------------------------------------------
#                                 GLOBAL VARIABLES
#-------------------------------------------------------------------------------

# the path to the entities parent folder
ENTITY_PATH ="src/entities"

# style sheets
style_sheet_title    = "font-size: 10pt; font-family: San-Serif;"
style_sheet_text     = "font-size: 10pt; font-family: San-Serif;"
style_sheet_required = "font-size: 10pt; font-family: San-Serif; color: red"
style_sheet_button   = "font-size: 10pt; font-family: San-Serif;"

#-------------------------------------------------------------------------------
#                                    MAIN CLASS
#-------------------------------------------------------------------------------

class CreateEntity(QtGui.QWidget):

    #---------------------------------------------------------------------------
    #                                 CONSTRUCTOR
    #---------------------------------------------------------------------------

    def __init__(self, parent = None):

        # super call
        super(CreateEntity, self).__init__()

        # a map from required settings to the associated required label
        self._required_map = {}

        # set up important variables
        self._file_path           = ''
        self._project_name        = ''
        self._sub_groups          = ''
        self._entity_name         = ''
        self._include_constructor = False
        self._include_destructor  = False
        self._description         = ''

        # set up the UI components
        self._init_ui()

    #---------------------------------------------------------------------------
    #                               PRIVATE METHODS
    #---------------------------------------------------------------------------

    # writes a line to the given file
    def _write_line(self, file, text):
        file.write(text + '\n')

    # writes a title to the file
    def _write_title(self, file, indent, text):
        # divider lines
        divider_line = (' ' * indent) + '//'
        divider_line += '-' * (80 - (indent + 2))
        # centered text
        title = (' ' * indent) + '//'
        centre = (80 - (len(title) + len(text) - 2)) / 2
        title += ' ' * centre
        title += str(text).upper()
        self._write_line(file, divider_line)
        self._write_line(file, title)
        self._write_line(file, divider_line)

    # write the entity header file to disk
    def _write_entity_header(self):

        # create the file name
        filename = self._file_path + '.hpp'
        # open the file
        file = open(filename, 'wb')

        # include guard
        include_guard = str(self._project_name).upper()
        include_guard += "_ENTITIES"
        for group in str(self._sub_groups).split('/'):
            if group == '' or group == ' ':
                continue
            include_guard += '_' + group.upper()
        include_guard += '_' + str(self._entity_name).upper()
        include_guard += '_H_'
        self._write_line(file, '#ifndef '     + include_guard)
        self._write_line(file, '#    define ' + include_guard)
        self._write_line(file, '')

        # include entity super class
        self._write_line(file, '#include "src/omicron/entity/Entity.hpp"')
        self._write_line(file, '')

        # class description
        if self._description != '':
            # sort the description so it's no longer than 80 lines
            box = []
            lines = str(self._description).split('\n')
            for line in lines:
                if (len(line) <= 76):
                    box.append(line + ' ')
                else:
                    shortened_line = ''
                    for word in line.split(' '):
                        if len(shortened_line) + len(word) <= 76:
                            shortened_line += word + ' '
                        else:
                            box.append(shortened_line)
                            shortened_line = word + ' '
                    box.append(shortened_line)

            # find the longest line
            longest_line = 0
            for line in box:
                if len(line) > longest_line:
                    longest_line = len(line)
            # add head and tail to the lines
            temp_box = box
            box = []
            for line in temp_box:
                box.append('| ' + line +
                    (' ' * (longest_line - len(line))) + '|')
            # write the description
            self._write_line(file, '/' + ('*' * longest_line) + '*\\')
            for line in box:
                self._write_line(file, line)
            self._write_line(file, '\\' + ('*' * longest_line) + '*/')

        # class begin
        self._write_line(file,
            'class ' + str(self._entity_name) + ' : public omi::Entity {')
        self._write_line(file, 'public:')
        self._write_line(file, '')

        # constructor if specified
        if self._include_constructor:
            self._write_title(file, 4, 'CONSTRUCTOR')
            self._write_line(file, '')
            self._write_line(file, '    ' + str(self._entity_name) + '();')
            self._write_line(file, '')

        # destructor if specified
        if self._include_destructor:
            self._write_title(file, 4, 'DESTRUCTOR')
            self._write_line(file, '')
            self._write_line(file, '    ~' + str(self._entity_name) + '();')
            self._write_line(file, '')

        # public member functions
        self._write_title(file, 4, 'PUBLIC MEMBER FUNCTIONS')
        self._write_line(file, '')
        self._write_line(file, '    /** #Override */')
        self._write_line(file, '    void init();')
        self._write_line(file, '')
        self._write_line(file, '    /** #Override */')
        self._write_line(file, '    void update();')

        # class end
        self._write_line(file, '};')

        # include guard end
        self._write_line(file, '')
        self._write_line(file, '#endif')

        # close the file
        file.close()

    # write the entity source file to disk
    def _write_entity_source(self):

        # create the file
        filename = self._file_path + '.cpp'
        # open the file
        file = open(filename, 'wb')

        # include header
        self._write_line(file, '#include "' + str(self._entity_name) + '.hpp"')
        self._write_line(file, '')

        # constructor if included
        if self._include_constructor:
            self._write_title(file, 0, 'CONSTRUCTOR')
            self._write_line(file, '')
            self._write_line(file, str(self._entity_name) + '::' +
                str(self._entity_name) + '()\n{')
            self._write_line(file, '}')
            self._write_line(file, '')

        # destructor if included
        if self._include_destructor:
            self._write_title(file, 0, 'DESTRUCTOR')
            self._write_line(file, '')
            self._write_line(file, str(self._entity_name) + '::~' +
                str(self._entity_name) + '()\n{')
            self._write_line(file, '}')
            self._write_line(file, '')

        # public member functions
        self._write_title(file, 0, 'PUBLIC MEMBER FUNCTIONS')
        self._write_line(file, '')
        self._write_line(file, 'void ' + str(self._entity_name) + '::init()\n{')
        self._write_line(file, '}')
        self._write_line(file, '')
        self._write_line(
            file, 'void ' + str(self._entity_name) + '::update()\n{')
        self._write_line(file, '}')
        self._write_line(file, '')

        # close the file
        file.close();

    # write the entity files to disk
    def _write_entity_files(self):

        # create the file path
        self._file_path = 'src/entities/' + self._sub_groups
        # check the file path exists if not create it
        if not os.path.exists(str(self._file_path)):
            os.makedirs(str(self._file_path))
        # finish making the file path
        self._file_path += '/' + self._entity_name

        # write the files
        self._write_entity_header()
        self._write_entity_source()


    #------------------------------CALLBACK METHODS-----------------------------


    def _project_name_callback(self, text):
        self._project_name = text

    def _sub_group_callback(self, text):
        self._sub_groups = text

    def _entity_name_callback(self, text):
        self._entity_name = text

    def _constructor_callback(self):
        # invert the setting
        self._include_constructor = not self._include_constructor

    def _destructor_callback(self):
        # invert the setting
        self._include_destructor = not self._include_destructor

    def _description_callback(self):
        self._description = self.description_edit.toPlainText()

    def _done_button_pressed(self):

        # check to make sure the required attributes are set
        fufilled = True
        for t, d in self._required_map.items():
            if t.text() == '':
                # we've found an empty required setting
                fufilled = False
                # show the required dialog
                d.setText('Required')
                d.adjustSize()
            else:
                # make sure the required dialog isn't showing
                d.setText('')
                d.adjustSize()

        # don't actually do anything since we don't have all the required data
        if not fufilled:
            return

        # write the entities file
        self._write_entity_files()
        # TODO: if this fails don't close

        # exit
        QtGui.QApplication.quit()

    def _cancel_button_pressed(self):
        # exit
        QtGui.QApplication.quit()


    #---------------------------------UI METHODS--------------------------------

    # creates a divider in the UI
    def _create_divider(self):
        divider = QtGui.QFrame()
        divider.setFrameShape(QtGui.QFrame.HLine)
        self.layout.addWidget(divider)

    # creates a title in the UI
    def _create_title(self, text):
        title = QtGui.QLabel(self)
        title.setStyleSheet(style_sheet_title)
        title.setText(str(text))
        title.adjustSize()
        self.layout.addWidget(title)

    # create a new text line setting
    def _create_text_line(self, call_back, required):
        text_edit = QtGui.QLineEdit(self)
        text_edit.setStyleSheet(style_sheet_text)
        text_edit.textChanged[str].connect(call_back)

        # add the required dialog if need
        if required:
            # make the label
            required_dialog = QtGui.QLabel(self)
            required_dialog.setStyleSheet(style_sheet_required)
            required_dialog.setText('Required')
            required_dialog.adjustSize()
            required_dialog.setText('')
            required_dialog.adjustSize()
            # set up a layout we can put the text box and dialog into
            required_layout = QtGui.QHBoxLayout()
            required_layout.addWidget(text_edit)
            required_layout.addWidget(required_dialog)
            # add to the main layout
            self.layout.addLayout(required_layout)
            # add to the map of required settings so we can check them later
            self._required_map[text_edit] = required_dialog
        # add just the text box the layout
        else:
            self.layout.addWidget(text_edit)

    # creates a check box setting
    def _create_check_box(self, text, call_back):
        check_box = QtGui.QCheckBox(text)
        check_box.setStyleSheet(style_sheet_title)
        check_box.toggled.connect(call_back)
        self.layout.addWidget(check_box)

    # sets up all the UI components
    def _init_ui(self):

        # the main layout
        self.layout = QtGui.QVBoxLayout()

        self._create_divider()


        #------------------------------PROJECT NAME-------------------------------------


        self._create_title('Project Name:')
        self._create_text_line(self._project_name_callback, True)

        #-------------------------------SUB GROUPS------------------------------


        self._create_title('Sub Groups:')
        self._create_text_line(self._sub_group_callback, False)


        #------------------------------ENTITY NAME------------------------------


        self._create_title('Entity Name:')
        self._create_text_line(self._entity_name_callback, True)


        #------------------------------CONSTRUCTOR------------------------------


        self._create_divider()

        self._create_check_box(
            'include constructor', self._constructor_callback)


        #-------------------------------DESTRUCTOR------------------------------


        self._create_check_box(
            'include destructor', self._destructor_callback)

        self._create_divider()


        #------------------------------DESCRIPTION------------------------------


        self._create_title('Description:')
        self.description_edit = QtGui.QTextEdit(self)
        self.description_edit.setStyleSheet(style_sheet_text)
        self.description_edit.textChanged.connect(self._description_callback)
        self.layout.addWidget(self.description_edit)


        #------------------------------DONE BUTTON------------------------------


        done_button = QtGui.QPushButton("Done", self)
        done_button.setStyleSheet(style_sheet_button)
        done_button.clicked.connect(self._done_button_pressed)


        #-----------------------------CANCEL BUTTON-----------------------------


        cancel_button = QtGui.QPushButton("Cancel", self)
        cancel_button.setStyleSheet(style_sheet_button)
        cancel_button.clicked.connect(self._cancel_button_pressed)


        #------------------------------FINAL SET UP-----------------------------


        # do the final set up for the buttons
        button_layout = QtGui.QHBoxLayout()
        button_layout.addStretch(1)
        button_layout.addWidget(done_button)
        button_layout.addWidget(cancel_button)
        button_layout.addStretch(1)
        self.layout.addStretch(1)
        self.layout.addLayout(button_layout)

        # set the layout on the window
        self.setLayout(self.layout)

        # set up and open the window
        self.setGeometry(200, 100, 600, 600)
        self.setWindowTitle('Create Omicron Entity')
        self.show()

#-------------------------------------------------------------------------------
#                                  MAIN FUNCTION
#-------------------------------------------------------------------------------

if __name__ == "__main__":

    app = QtGui.QApplication(sys.argv)
    entityCreator = CreateEntity()
    sys.exit(app.exec_())
