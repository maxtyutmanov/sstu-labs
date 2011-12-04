IF EXISTS (
	SELECT 
		*
	FROM 
		sys.objects
	WHERE
		type = 'P' AND
		name = 'AddEvent'
)
DROP PROCEDURE [AddEvent]

GO

CREATE PROCEDURE [AddEvent]
	@eventTypeID INT,
	@message NVARCHAR(MAX)
AS
BEGIN
	INSERT INTO [Events]
	([EventTypeID], [Message])
	VALUES
	(@eventTypeID, @message)
END

GO