PROGRAM ifelse;
var x:integer;
BEGIN
	x := 10;
	IF x < 5 THEN
		BEGIN
			WRITELN('in if');
		END
    else
    	BEGIN
        	WRITELN('in else');
        END
END.