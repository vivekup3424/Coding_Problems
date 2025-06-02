# This files contains your custom actions which can be used to run
# custom Python code.
#
# See this guide on how to implement these action:
# https://rasa.com/docs/rasa/custom-actions


from typing import Any, Text, Dict, List
from rasa_sdk import Action, Tracker
from rasa_sdk.executor import CollectingDispatcher
from rasa_sdk.events import SlotSet


class ActionTurnOnFan(Action):

    def name(self) -> Text:
        return "action_turn_on_fan"

    def run(self, dispatcher: CollectingDispatcher,
            tracker: Tracker,
            domain: Dict[Text, Any]) -> List[Dict[Text, Any]]:

        location = tracker.get_slot("device_location")
        device_name = tracker.get_slot("device_name")
        
        # Simulate smart device control
        if location:
            message = f"Turning on the fan in the {location}."
        elif device_name:
            message = f"Turning on the {device_name}."
        else:
            message = "Turning on the fan."
            
        # Here you would integrate with your smart home system
        # For now, we'll just simulate the action
        
        dispatcher.utter_message(text=message)
        
        return []


class ActionTurnOffFan(Action):

    def name(self) -> Text:
        return "action_turn_off_fan"

    def run(self, dispatcher: CollectingDispatcher,
            tracker: Tracker,
            domain: Dict[Text, Any]) -> List[Dict[Text, Any]]:

        location = tracker.get_slot("device_location")
        device_name = tracker.get_slot("device_name")
        
        if location == "all":
            message = "Turning off all fans in the house."
        elif location:
            message = f"Turning off the fan in the {location}."
        elif device_name:
            message = f"Turning off the {device_name}."
        else:
            message = "Turning off the fan."
            
        dispatcher.utter_message(text=message)
        
        return []


class ActionAdjustFanSpeed(Action):

    def name(self) -> Text:
        return "action_adjust_fan_speed"

    def run(self, dispatcher: CollectingDispatcher,
            tracker: Tracker,
            domain: Dict[Text, Any]) -> List[Dict[Text, Any]]:

        location = tracker.get_slot("device_location")
        fan_speed = tracker.get_slot("fan_speed")
        device_name = tracker.get_slot("device_name")
        
        if not fan_speed:
            dispatcher.utter_message(text="What speed would you like to set the fan to?")
            return []
        
        if location:
            message = f"Setting the {location} fan speed to {fan_speed}."
        elif device_name:
            message = f"Setting the {device_name} speed to {fan_speed}."
        else:
            message = f"Setting fan speed to {fan_speed}."
            
        dispatcher.utter_message(text=message)
        
        return []


class ActionTurnOnAC(Action):

    def name(self) -> Text:
        return "action_turn_on_ac"

    def run(self, dispatcher: CollectingDispatcher,
            tracker: Tracker,
            domain: Dict[Text, Any]) -> List[Dict[Text, Any]]:

        location = tracker.get_slot("device_location")
        device_name = tracker.get_slot("device_name")
        
        if location:
            message = f"Turning on the AC in the {location}."
        elif device_name:
            message = f"Turning on the {device_name}."
        else:
            message = "Turning on the air conditioning."
            
        dispatcher.utter_message(text=message)
        
        return []


class ActionTurnOffAC(Action):

    def name(self) -> Text:
        return "action_turn_off_ac"

    def run(self, dispatcher: CollectingDispatcher,
            tracker: Tracker,
            domain: Dict[Text, Any]) -> List[Dict[Text, Any]]:

        location = tracker.get_slot("device_location")
        device_name = tracker.get_slot("device_name")
        
        if location == "all":
            message = "Turning off all AC units in the house."
        elif location:
            message = f"Turning off the AC in the {location}."
        elif device_name:
            message = f"Turning off the {device_name}."
        else:
            message = "Turning off the air conditioning."
            
        dispatcher.utter_message(text=message)
        
        return []


class ActionAdjustTemperature(Action):

    def name(self) -> Text:
        return "action_adjust_temperature"

    def run(self, dispatcher: CollectingDispatcher,
            tracker: Tracker,
            domain: Dict[Text, Any]) -> List[Dict[Text, Any]]:

        location = tracker.get_slot("device_location")
        temperature = tracker.get_slot("temperature")
        device_name = tracker.get_slot("device_name")
        
        if not temperature:
            dispatcher.utter_message(text="What temperature would you like to set?")
            return []
        
        if location:
            message = f"Setting the {location} AC temperature to {temperature} degrees."
        elif device_name:
            message = f"Setting the {device_name} temperature to {temperature} degrees."
        else:
            message = f"Setting AC temperature to {temperature} degrees."
            
        dispatcher.utter_message(text=message)
        
        return []


class ActionChangeACMode(Action):

    def name(self) -> Text:
        return "action_change_ac_mode"

    def run(self, dispatcher: CollectingDispatcher,
            tracker: Tracker,
            domain: Dict[Text, Any]) -> List[Dict[Text, Any]]:

        location = tracker.get_slot("device_location")
        ac_mode = tracker.get_slot("ac_mode")
        device_name = tracker.get_slot("device_name")
        
        if not ac_mode:
            dispatcher.utter_message(text="What mode would you like to set? (cool, heat, auto, dry, fan_only)")
            return []
        
        if location:
            message = f"Setting the {location} AC to {ac_mode} mode."
        elif device_name:
            message = f"Setting the {device_name} to {ac_mode} mode."
        else:
            message = f"Setting AC to {ac_mode} mode."
            
        dispatcher.utter_message(text=message)
        
        return []


class ActionAdjustACSpeed(Action):

    def name(self) -> Text:
        return "action_adjust_ac_speed"

    def run(self, dispatcher: CollectingDispatcher,
            tracker: Tracker,
            domain: Dict[Text, Any]) -> List[Dict[Text, Any]]:

        location = tracker.get_slot("device_location")
        ac_speed = tracker.get_slot("ac_speed")
        device_name = tracker.get_slot("device_name")
        
        if not ac_speed:
            dispatcher.utter_message(text="What fan speed would you like? (low, medium, high, auto)")
            return []
        
        if location:
            message = f"Setting the {location} AC fan speed to {ac_speed}."
        elif device_name:
            message = f"Setting the {device_name} fan speed to {ac_speed}."
        else:
            message = f"Setting AC fan speed to {ac_speed}."
            
        dispatcher.utter_message(text=message)
        
        return []


class ActionTurnOnLights(Action):

    def name(self) -> Text:
        return "action_turn_on_lights"

    def run(self, dispatcher: CollectingDispatcher,
            tracker: Tracker,
            domain: Dict[Text, Any]) -> List[Dict[Text, Any]]:

        location = tracker.get_slot("device_location")
        device_name = tracker.get_slot("device_name")
        
        if location:
            message = f"Turning on the lights in the {location}."
        elif device_name:
            message = f"Turning on the {device_name}."
        else:
            message = "Turning on the lights."
            
        dispatcher.utter_message(text=message)
        
        return []


class ActionTurnOffLights(Action):

    def name(self) -> Text:
        return "action_turn_off_lights"

    def run(self, dispatcher: CollectingDispatcher,
            tracker: Tracker,
            domain: Dict[Text, Any]) -> List[Dict[Text, Any]]:

        location = tracker.get_slot("device_location")
        device_name = tracker.get_slot("device_name")
        
        if location == "all":
            message = "Turning off all lights in the house."
        elif location:
            message = f"Turning off the lights in the {location}."
        elif device_name:
            message = f"Turning off the {device_name}."
        else:
            message = "Turning off the lights."
            
        dispatcher.utter_message(text=message)
        
        return []


class ActionAdjustBrightness(Action):

    def name(self) -> Text:
        return "action_adjust_brightness"

    def run(self, dispatcher: CollectingDispatcher,
            tracker: Tracker,
            domain: Dict[Text, Any]) -> List[Dict[Text, Any]]:

        location = tracker.get_slot("device_location")
        brightness_level = tracker.get_slot("brightness_level")
        device_name = tracker.get_slot("device_name")
        
        if not brightness_level:
            dispatcher.utter_message(text="What brightness level would you like?")
            return []
        
        if location:
            message = f"Setting the {location} lights brightness to {brightness_level}."
        elif device_name:
            message = f"Setting the {device_name} brightness to {brightness_level}."
        else:
            message = f"Setting lights brightness to {brightness_level}."
            
        dispatcher.utter_message(text=message)
        
        return []


class ActionChangeLightColor(Action):

    def name(self) -> Text:
        return "action_change_light_color"

    def run(self, dispatcher: CollectingDispatcher,
            tracker: Tracker,
            domain: Dict[Text, Any]) -> List[Dict[Text, Any]]:

        location = tracker.get_slot("device_location")
        light_color = tracker.get_slot("light_color")
        device_name = tracker.get_slot("device_name")
        
        if not light_color:
            dispatcher.utter_message(text="What color would you like the lights to be?")
            return []
        
        if location:
            message = f"Changing the {location} lights to {light_color}."
        elif device_name:
            message = f"Changing the {device_name} to {light_color}."
        else:
            message = f"Changing lights to {light_color}."
            
        dispatcher.utter_message(text=message)
        
        return []


class ActionChangeLightMode(Action):

    def name(self) -> Text:
        return "action_change_light_mode"

    def run(self, dispatcher: CollectingDispatcher,
            tracker: Tracker,
            domain: Dict[Text, Any]) -> List[Dict[Text, Any]]:

        location = tracker.get_slot("device_location")
        light_mode = tracker.get_slot("light_mode")
        device_name = tracker.get_slot("device_name")
        
        if not light_mode:
            dispatcher.utter_message(text="What lighting mode would you like? (reading, party, romantic, sleep, work, normal)")
            return []
        
        if location:
            message = f"Setting the {location} lights to {light_mode} mode."
        elif device_name:
            message = f"Setting the {device_name} to {light_mode} mode."
        else:
            message = f"Setting lights to {light_mode} mode."
            
        dispatcher.utter_message(text=message)
        
        return []


class ActionDimLights(Action):

    def name(self) -> Text:
        return "action_dim_lights"

    def run(self, dispatcher: CollectingDispatcher,
            tracker: Tracker,
            domain: Dict[Text, Any]) -> List[Dict[Text, Any]]:

        location = tracker.get_slot("device_location")
        device_name = tracker.get_slot("device_name")
        
        if location:
            message = f"Dimming the lights in the {location}."
        elif device_name:
            message = f"Dimming the {device_name}."
        else:
            message = "Dimming the lights."
            
        dispatcher.utter_message(text=message)
        
        return []


class ActionBrightenLights(Action):

    def name(self) -> Text:
        return "action_brighten_lights"

    def run(self, dispatcher: CollectingDispatcher,
            tracker: Tracker,
            domain: Dict[Text, Any]) -> List[Dict[Text, Any]]:

        location = tracker.get_slot("device_location")
        device_name = tracker.get_slot("device_name")
        
        if location:
            message = f"Brightening the lights in the {location}."
        elif device_name:
            message = f"Brightening the {device_name}."
        else:
            message = "Brightening the lights."
            
        dispatcher.utter_message(text=message)
        
        return []


class ActionDefaultFallback(Action):

    def name(self) -> Text:
        return "action_default_fallback"

    def run(self, dispatcher: CollectingDispatcher,
            tracker: Tracker,
            domain: Dict[Text, Any]) -> List[Dict[Text, Any]]:

        dispatcher.utter_message(response="utter_default")
        
        return []
