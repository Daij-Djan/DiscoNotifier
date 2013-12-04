/*
 *  $Id: SCEvent.h 195 2011-03-15 21:47:34Z stuart $
 *
 *  SCEvents
 *  http://stuconnolly.com/projects/code/
 *
 *  Copyright (c) 2011 Stuart Connolly. All rights reserved.
 *
 *  Permission is hereby granted, free of charge, to any person
 *  obtaining a copy of this software and associated documentation
 *  files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use,
 *  copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following
 *  conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *  OTHER DEALINGS IN THE SOFTWARE.
 */

#import <Foundation/Foundation.h>
#import <CoreServices/CoreServices.h>

#import "SCConstants.h"

/**
 * @class SCEvent SCEvent.h
 *
 * @author Stuart Connolly http://stuconnolly.com/
 *
 * Class representing a single file system event.
 */
@interface SCEvent : NSObject 
{
    NSUInteger _eventId;
    NSDate *_eventDate;
    NSString *_eventPath;
    SCEventFlags _eventFlags;
}

/**
 * @property _eventId The ID of the event.
 */
@property (readwrite, assign) NSUInteger eventId;

/**
 * @property _eventDate The date of the event.
 */
@property (readwrite, retain) NSDate *eventDate;

/**
 * @property _eventPath The file system path of the event.
 */
@property (readwrite, retain) NSString *eventPath;

/**
 * @property _eventFlag The flags that are associated with the event.
 */
@property (readwrite, assign) SCEventFlags eventFlags;

/**
 * Returns an initialized instance of SCEvent using the supplied event ID, date, path
 * and flag.
 *
 * @param identifer The ID of the event
 * @param date      The date of the event
 * @param path      The file system path of the event
 * @param flags     The flags associated with the event
 *
 * @return The initialized (autoreleased) instance
 */
+ (SCEvent *)eventWithEventId:(NSUInteger)identifier
					eventDate:(NSDate *)date 
					eventPath:(NSString *)path 
					eventFlags:(SCEventFlags)flags;

/**
 * Initializes an instance of SCEvent using the supplied event ID, path and flag.
 *
 * @param identifer The ID of the event
 * @param date      The date of the event
 * @param path      The file system path of the event
 * @param flags     The flags associated with the event
 *
 * @return The initialized instance
 */
- (id)initWithEventId:(NSUInteger)identifier
			eventDate:(NSDate *)date 
			eventPath:(NSString *)path 
			eventFlags:(SCEventFlags)flags;

@end
