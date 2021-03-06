﻿//------------------------------------------------------------------------------
// <auto-generated>
//    This code was generated from a template.
//
//    Manual changes to this file may cause unexpected behavior in your application.
//    Manual changes to this file will be overwritten if the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

using System;
using System.Data.Objects;
using System.Data.Objects.DataClasses;
using System.Data.EntityClient;
using System.ComponentModel;
using System.Xml.Serialization;
using System.Runtime.Serialization;

[assembly: EdmSchemaAttribute()]
#region EDM Relationship Metadata

[assembly: EdmRelationshipAttribute("JustServerLogModel", "FK__Events__EventTyp__0EA330E9", "EventTypes", System.Data.Metadata.Edm.RelationshipMultiplicity.One, typeof(JustServer.LoggerUI.EventType), "Events", System.Data.Metadata.Edm.RelationshipMultiplicity.Many, typeof(JustServer.LoggerUI.Event), true)]

#endregion

namespace JustServer.LoggerUI
{
    #region Contexts
    
    /// <summary>
    /// No Metadata Documentation available.
    /// </summary>
    public partial class JustServerLogEntities : ObjectContext
    {
        #region Constructors
    
        /// <summary>
        /// Initializes a new JustServerLogEntities object using the connection string found in the 'JustServerLogEntities' section of the application configuration file.
        /// </summary>
        public JustServerLogEntities() : base("name=JustServerLogEntities", "JustServerLogEntities")
        {
            this.ContextOptions.LazyLoadingEnabled = true;
            OnContextCreated();
        }
    
        /// <summary>
        /// Initialize a new JustServerLogEntities object.
        /// </summary>
        public JustServerLogEntities(string connectionString) : base(connectionString, "JustServerLogEntities")
        {
            this.ContextOptions.LazyLoadingEnabled = true;
            OnContextCreated();
        }
    
        /// <summary>
        /// Initialize a new JustServerLogEntities object.
        /// </summary>
        public JustServerLogEntities(EntityConnection connection) : base(connection, "JustServerLogEntities")
        {
            this.ContextOptions.LazyLoadingEnabled = true;
            OnContextCreated();
        }
    
        #endregion
    
        #region Partial Methods
    
        partial void OnContextCreated();
    
        #endregion
    
        #region ObjectSet Properties
    
        /// <summary>
        /// No Metadata Documentation available.
        /// </summary>
        public ObjectSet<Event> Events
        {
            get
            {
                if ((_Events == null))
                {
                    _Events = base.CreateObjectSet<Event>("Events");
                }
                return _Events;
            }
        }
        private ObjectSet<Event> _Events;
    
        /// <summary>
        /// No Metadata Documentation available.
        /// </summary>
        public ObjectSet<EventType> EventTypes
        {
            get
            {
                if ((_EventTypes == null))
                {
                    _EventTypes = base.CreateObjectSet<EventType>("EventTypes");
                }
                return _EventTypes;
            }
        }
        private ObjectSet<EventType> _EventTypes;

        #endregion
        #region AddTo Methods
    
        /// <summary>
        /// Deprecated Method for adding a new object to the Events EntitySet. Consider using the .Add method of the associated ObjectSet&lt;T&gt; property instead.
        /// </summary>
        public void AddToEvents(Event @event)
        {
            base.AddObject("Events", @event);
        }
    
        /// <summary>
        /// Deprecated Method for adding a new object to the EventTypes EntitySet. Consider using the .Add method of the associated ObjectSet&lt;T&gt; property instead.
        /// </summary>
        public void AddToEventTypes(EventType eventType)
        {
            base.AddObject("EventTypes", eventType);
        }

        #endregion
    }
    

    #endregion
    
    #region Entities
    
    /// <summary>
    /// No Metadata Documentation available.
    /// </summary>
    [EdmEntityTypeAttribute(NamespaceName="JustServerLogModel", Name="Event")]
    [Serializable()]
    [DataContractAttribute(IsReference=true)]
    public partial class Event : EntityObject
    {
        #region Factory Method
    
        /// <summary>
        /// Create a new Event object.
        /// </summary>
        /// <param name="id">Initial value of the ID property.</param>
        /// <param name="eventTypeID">Initial value of the EventTypeID property.</param>
        /// <param name="eventTime">Initial value of the EventTime property.</param>
        /// <param name="message">Initial value of the Message property.</param>
        public static Event CreateEvent(global::System.Int32 id, global::System.Int32 eventTypeID, global::System.DateTime eventTime, global::System.String message)
        {
            Event @event = new Event();
            @event.ID = id;
            @event.EventTypeID = eventTypeID;
            @event.EventTime = eventTime;
            @event.Message = message;
            return @event;
        }

        #endregion
        #region Primitive Properties
    
        /// <summary>
        /// No Metadata Documentation available.
        /// </summary>
        [EdmScalarPropertyAttribute(EntityKeyProperty=true, IsNullable=false)]
        [DataMemberAttribute()]
        public global::System.Int32 ID
        {
            get
            {
                return _ID;
            }
            set
            {
                if (_ID != value)
                {
                    OnIDChanging(value);
                    ReportPropertyChanging("ID");
                    _ID = StructuralObject.SetValidValue(value);
                    ReportPropertyChanged("ID");
                    OnIDChanged();
                }
            }
        }
        private global::System.Int32 _ID;
        partial void OnIDChanging(global::System.Int32 value);
        partial void OnIDChanged();
    
        /// <summary>
        /// No Metadata Documentation available.
        /// </summary>
        [EdmScalarPropertyAttribute(EntityKeyProperty=false, IsNullable=false)]
        [DataMemberAttribute()]
        public global::System.Int32 EventTypeID
        {
            get
            {
                return _EventTypeID;
            }
            set
            {
                OnEventTypeIDChanging(value);
                ReportPropertyChanging("EventTypeID");
                _EventTypeID = StructuralObject.SetValidValue(value);
                ReportPropertyChanged("EventTypeID");
                OnEventTypeIDChanged();
            }
        }
        private global::System.Int32 _EventTypeID;
        partial void OnEventTypeIDChanging(global::System.Int32 value);
        partial void OnEventTypeIDChanged();
    
        /// <summary>
        /// No Metadata Documentation available.
        /// </summary>
        [EdmScalarPropertyAttribute(EntityKeyProperty=false, IsNullable=false)]
        [DataMemberAttribute()]
        public global::System.DateTime EventTime
        {
            get
            {
                return _EventTime;
            }
            set
            {
                OnEventTimeChanging(value);
                ReportPropertyChanging("EventTime");
                _EventTime = StructuralObject.SetValidValue(value);
                ReportPropertyChanged("EventTime");
                OnEventTimeChanged();
            }
        }
        private global::System.DateTime _EventTime;
        partial void OnEventTimeChanging(global::System.DateTime value);
        partial void OnEventTimeChanged();
    
        /// <summary>
        /// No Metadata Documentation available.
        /// </summary>
        [EdmScalarPropertyAttribute(EntityKeyProperty=false, IsNullable=false)]
        [DataMemberAttribute()]
        public global::System.String Message
        {
            get
            {
                return _Message;
            }
            set
            {
                OnMessageChanging(value);
                ReportPropertyChanging("Message");
                _Message = StructuralObject.SetValidValue(value, false);
                ReportPropertyChanged("Message");
                OnMessageChanged();
            }
        }
        private global::System.String _Message;
        partial void OnMessageChanging(global::System.String value);
        partial void OnMessageChanged();

        #endregion
    
        #region Navigation Properties
    
        /// <summary>
        /// No Metadata Documentation available.
        /// </summary>
        [XmlIgnoreAttribute()]
        [SoapIgnoreAttribute()]
        [DataMemberAttribute()]
        [EdmRelationshipNavigationPropertyAttribute("JustServerLogModel", "FK__Events__EventTyp__0EA330E9", "EventTypes")]
        public EventType EventType
        {
            get
            {
                return ((IEntityWithRelationships)this).RelationshipManager.GetRelatedReference<EventType>("JustServerLogModel.FK__Events__EventTyp__0EA330E9", "EventTypes").Value;
            }
            set
            {
                ((IEntityWithRelationships)this).RelationshipManager.GetRelatedReference<EventType>("JustServerLogModel.FK__Events__EventTyp__0EA330E9", "EventTypes").Value = value;
            }
        }
        /// <summary>
        /// No Metadata Documentation available.
        /// </summary>
        [BrowsableAttribute(false)]
        [DataMemberAttribute()]
        public EntityReference<EventType> EventTypeReference
        {
            get
            {
                return ((IEntityWithRelationships)this).RelationshipManager.GetRelatedReference<EventType>("JustServerLogModel.FK__Events__EventTyp__0EA330E9", "EventTypes");
            }
            set
            {
                if ((value != null))
                {
                    ((IEntityWithRelationships)this).RelationshipManager.InitializeRelatedReference<EventType>("JustServerLogModel.FK__Events__EventTyp__0EA330E9", "EventTypes", value);
                }
            }
        }

        #endregion
    }
    
    /// <summary>
    /// No Metadata Documentation available.
    /// </summary>
    [EdmEntityTypeAttribute(NamespaceName="JustServerLogModel", Name="EventType")]
    [Serializable()]
    [DataContractAttribute(IsReference=true)]
    public partial class EventType : EntityObject
    {
        #region Factory Method
    
        /// <summary>
        /// Create a new EventType object.
        /// </summary>
        /// <param name="id">Initial value of the ID property.</param>
        /// <param name="name">Initial value of the Name property.</param>
        public static EventType CreateEventType(global::System.Int32 id, global::System.String name)
        {
            EventType eventType = new EventType();
            eventType.ID = id;
            eventType.Name = name;
            return eventType;
        }

        #endregion
        #region Primitive Properties
    
        /// <summary>
        /// No Metadata Documentation available.
        /// </summary>
        [EdmScalarPropertyAttribute(EntityKeyProperty=true, IsNullable=false)]
        [DataMemberAttribute()]
        public global::System.Int32 ID
        {
            get
            {
                return _ID;
            }
            set
            {
                if (_ID != value)
                {
                    OnIDChanging(value);
                    ReportPropertyChanging("ID");
                    _ID = StructuralObject.SetValidValue(value);
                    ReportPropertyChanged("ID");
                    OnIDChanged();
                }
            }
        }
        private global::System.Int32 _ID;
        partial void OnIDChanging(global::System.Int32 value);
        partial void OnIDChanged();
    
        /// <summary>
        /// No Metadata Documentation available.
        /// </summary>
        [EdmScalarPropertyAttribute(EntityKeyProperty=false, IsNullable=false)]
        [DataMemberAttribute()]
        public global::System.String Name
        {
            get
            {
                return _Name;
            }
            set
            {
                OnNameChanging(value);
                ReportPropertyChanging("Name");
                _Name = StructuralObject.SetValidValue(value, false);
                ReportPropertyChanged("Name");
                OnNameChanged();
            }
        }
        private global::System.String _Name;
        partial void OnNameChanging(global::System.String value);
        partial void OnNameChanged();

        #endregion
    
        #region Navigation Properties
    
        /// <summary>
        /// No Metadata Documentation available.
        /// </summary>
        [XmlIgnoreAttribute()]
        [SoapIgnoreAttribute()]
        [DataMemberAttribute()]
        [EdmRelationshipNavigationPropertyAttribute("JustServerLogModel", "FK__Events__EventTyp__0EA330E9", "Events")]
        public EntityCollection<Event> Events
        {
            get
            {
                return ((IEntityWithRelationships)this).RelationshipManager.GetRelatedCollection<Event>("JustServerLogModel.FK__Events__EventTyp__0EA330E9", "Events");
            }
            set
            {
                if ((value != null))
                {
                    ((IEntityWithRelationships)this).RelationshipManager.InitializeRelatedCollection<Event>("JustServerLogModel.FK__Events__EventTyp__0EA330E9", "Events", value);
                }
            }
        }

        #endregion
    }

    #endregion
    
}
