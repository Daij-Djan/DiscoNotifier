/*
 *  $Id: SCEvents.h 205 2011-06-18 15:16:08Z stuart $
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

#import "SCEventListenerProtocol.h"

@class SCEvent;

/**
 * @class SCEvents SCEvents.h
 *
 * @author Stuart Connolly http://stuconnolly.com/
 *
 * An Objective-C wrapper for the FSEvents C API.
 */
@interface SCEvents : NSObject 
{
	CFRunLoopRef         _runLoop;
    FSEventStreamRef     _eventStream;
	FSEventStreamEventId _resumeFromEventId;
      
	pthread_mutex_t       _eventsLock;
}

/**
 * @property delegate The delegate that SCEvents is to notify when events occur
 */
@property (readwrite, weak) id <NSObject, SCEventListenerProtocol> delegate;

/**
 * @property isWatchingPaths Indicates whether the events stream is currently running
 */
@property (readonly, getter=isWatchingPaths) BOOL watchingPaths;

/**
 * @property ignoreEventsFromSubDirs Indicates whether events from sub-directories of the excluded paths are ignored. Defaults to YES.
 */
@property (readwrite, assign) BOOL ignoreEventsFromSubDirs;

/**
 * @property lastEvent The last event that occurred and that was delivered to the delegate.
 */
@property (readwrite, retain) SCEvent *lastEvent;

/**
 * @property notificationLatency The latency time of which SCEvents is notified by FSEvents of events. Defaults to 3 seconds.
 */
@property (readwrite, assign) NSTimeInterval notificationLatency;

/**
 * @property watchedPaths The paths that are to be watched for events.
 */
@property (readwrite, retain) NSArray *watchedPaths;

/**
 * @property excludedPaths the path to be ignored
 */
@property (readwrite, retain) NSArray *excludedPaths;

/**
 * @property resumeFromEventId The event ID from which to resume from when the stream is started.
 */
@property (readwrite, assign) FSEventStreamEventId resumeFromEventId;

/**
 * Flushes the event stream synchronously by sending events that have already
 * occurred but not yet delivered.
 *
 * @return A BOOL indicating the sucess or failure
 */
- (BOOL)flushEventStreamSync;

/**
 * Flushes the event stream asynchronously by sending events that have already
 * occurred but not yet delivered.
 *
 * @return A BOOL indicating the sucess or failure
 */
- (BOOL)flushEventStreamAsync;

/**
 * Starts watching the supplied array of paths for events on the current run loop.
 *
 * @param paths An array of paths to watch
 *
 * @return A BOOL indicating the success or failure
 */
- (BOOL)startWatchingPaths:(NSArray *)paths;

/**
 * Starts watching the supplied array of paths for events on the supplied run loop.
 * A boolean value is returned to indicate the success of starting the stream. If
 * there are no paths to watch or the stream is already running then false is
 * returned.
 *
 * @param paths   An array of paths to watch
 * @param runLoop The runloop the events stream is to be scheduled on
 *
 * @return A BOOL indicating the success or failure
 */
- (BOOL)startWatchingPaths:(NSArray *)paths onRunLoop:(NSRunLoop *)runLoop;

/**
 * Stops the event stream from watching the set paths. A boolean value is returned
 * to indicate the success of stopping the stream. False is return if this method
 * is called when the stream is not already running.
 *
 * @return A BOOL indicating the success or failure
 */
- (BOOL)stopWatchingPaths;

/**
 * Provides a description of the event stream. Useful for debugging purposes.
 *
 * @return The description string
 */
- (NSString *)streamDescription;

@end
