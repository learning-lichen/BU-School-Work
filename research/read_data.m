% Author: Max Gale

text = fileread('/Users/max/workplace/school/research/test_data.csv');
column_names = {};   % Column names
cytometer_data = {}; % Matrix containing the flow cytometer data.

% Get the locations of newlines, and add a new one at the end.
newlines = find(text == char(10));
newlines = [newlines(:);length(text) + 1];

% Get the locations of the semicolons.
semicolons = find(text == ';');

% Read the column names.
index = 1;
counter = 1;

while index < newlines(1)
   name = text(index:min(semicolons(counter), newlines(1)) - 1);
   column_names{end + 1, 1} = name;
   
   index = semicolons(counter) + 1;
   counter = counter + 1;
end

% There are 16 columns in the data set.
column_counter = 1;
row_counter = 2;
counter = 1;

% Find the first semicolon after the first newline
while newlines(1) > semicolons(counter)
    counter = counter + 1;
end

while newlines(row_counter) < newlines(end)
    while column_counter < 16
        text_val = text(min(semicolons(counter), ...
                            newlines(row_counter + 1)) - 1);
        
        cytometer_data{row, col} = text_val;
        
        column_counter = column_counter + 1;
        counter = counter + 1;
    end
    
    row_counter = row_counter + 1;
    column_counter = 1;
end

disp(cytometer_data);