//
//  NNAApplication.h
//  VectorWorks
//
//  Created by Lyndsey Ferguson on 12/17/12.
//
//

#import <Cocoa/Cocoa.h>
#import "NNAVWHostApplicationProtocol.h"

@interface NNAApplication : NSApplication<NNAVWHostApplicationProtocol>
{
    NSWindow* _popoverModalWindow;
    
    /*!
     * Product name, suitable for display on
     *  windows, etc.
     */
    NSString* _productSpecificDisplayName;
    
    /*!
     *  Stack of modal windows that are immediately
     *   active within the application (stack is
     *   arranged in increasing Z-order/
     *   chronological order with respect to
     *   window invocation time).
     */
    NSObject* _modalWindowStack;

    /*!
     *  Window that was the key window before the
     *   invocation of a modal dialog/stack of
     *   modal dialogs
     */
    NSWindow* _lastKeyWindowBeforeModalInvocation;
    
    /*!
     *  Reference to the current Layout Manager
     *   dialog that is in the process of closing
     */
    NSWindow* _currentLayoutManagerDialogInClosureState;
	
    /*!
     *  Collection of all windows that existed before
     *   the invocation of the first modal window within
     *   a modal window stack (the collection weakly
     *   references windows, and theremore may contain nil
     *   members).
     */
    NSPointerArray* _appWindowSetBeforeModalInvocation;

	/*!
	 * handlingSendEvent variable is used by CEF framework itself
	 * not necessarily used within vectorworks
	 * Date: Nov 9, 2017
	 */
	BOOL _handlingSendEvent;
	
    /*!
     *  Collection of window objects that require explicit key equivalent
     *   handling (primarily for the particular set of general, editing
     *   key equivalents - cut, copy, paste, undo, etc.).
     */
	NSPointerArray* _windowsRequiringExplicitKeyEquivalentHandling;
    
    /*!
     * Menu that is currently activated
     */
    NSMenu* __weak _currentlyActiveMenu;
}

@property(retain, nonatomic) NSWindow* popoverModalWindow;

-(NSInteger)runPopoverModalForWindow:(NSWindow*)window;
-(void)stopPopoverModalWindow;
-(void)cancelPopoverModalWindowDueToApplicationDeactivation;
-(void)conditionallyCorrectModalWindowOrdering;
-(id)handleOpenScriptCommand:(NSScriptCommand*)scriptCommand;
-(NSArray<NSObject*>*)orderedDocuments;

/*!
 *  Suggests whether or not a particular window should
 *   acquire key window status, based upon the current
 *   internal state of other window arrangements, etc.
 *
 *  @param queryWindow The window for which key window
 *                     status acquisition is to be
 *                     suggested
 *
 *  @return YES if the window should acquire key window
 *          status
 *
 *  @author Ayodeji Oshinnaiye, August 1, 2017
 */
-(BOOL)suggestKeyStatusAcquisitionForWindow: (NSWindow*) queryWindow;

/*!
 *  Overridden from NNAVWHostApplicationProtocol
 *  @see NNAVWHostApplicationProtocol#requestExplicitKeyEquivalentHandling
 */
- (void)requestExplicitKeyEquivalentHandling: (NSWindow*) targetWindow;

/*!
 *  Retrieves the previous window in the collection
 *   of application-owned windows
 *
 *  @param startingWindow  The window in the set of
 *                         application-owned windows
 *                         for which the previous
 *                         window should be obtained
 *  @param cyclicIteration When set to YES, the window
 *                         collection is treated as a
 *                         cyclic container (nil is
 *                         never returned if a collection
 *                         terminal point is reached)
 *
 *  @return A window object upon success, nil otherwise
 *
 *  @author Ayodeji Oshinnaiye, December 21, 2015
 */
-(NSWindow*)previousWindow: (NSWindow*)startingWindow
       withCyclicIteration: (BOOL)cyclicIteration;

/*!
 *  Retrieves the next window in the collection
 *   of application-owned windows
 *
 *  @param startingWindow  The window in the set of
 *                         application-owned windows
 *                         for which the next
 *                         window should be obtained
 *  @param cyclicIteration When set to YES, the window
 *                         collection is treated as a
 *                         cyclic container (nil is
 *                         never returned if a collection
 *                         terminal point is reached)
 *
 *  @return A window object upon success, nil otherwise
 *
 *  @author Ayodeji Oshinnaiye, December 21, 2015
 */
-(NSWindow*)nextWindow: (NSWindow*)startingWindow
   withCyclicIteration: (BOOL)cyclicIteration;

/*!
 *  Retrieves the previous window in the collection
 *   of application-owned windows
 *
 *  @param startingWindow  The window in the set of
 *                         application-owned windows
 *                         for which the previous
 *                         window should be obtained
 *  @param cyclicIteration When set to YES, the window
 *                         collection is treated as a
 *                         cyclic container (nil is
 *                         never returned if a collection
 *                         terminal point is reached)
 *  @param filterPredicate Predicate used to determine the
 *                         set of windows for which the
 *                         previous window will be retrieved
 *                         (can be nil; starting window
 *                         must comply with predicate
 *                         logic)
 *
 *  @return A window object upon success, nil otherwise
 *
 *  @author Ayodeji Oshinnaiye, December 21, 2015
 */
-(NSWindow*)previousWindow: (NSWindow*)startingWindow
       withCyclicIteration: (BOOL)cyclicIteration
       withFilterPredicate: (NSPredicate*)filterPredicate;

/*!
 *  Retrieves the next window in the collection
 *   of application-owned windows
 *
 *  @param startingWindow  The window in the set of
 *                         application-owned windows
 *                         for which the next
 *                         window should be obtained
 *  @param cyclicIteration When set to YES, the window
 *                         collection is treated as a
 *                         cyclic container (nil is
 *                         never returned if a collection
 *                         terminal point is reached)
 *  @param filterPredicate Predicate used to determine the
 *                         set of windows for which the
 *                         next window will be retrieved
 *                         (can be nil; starting window
 *                         must comply with predicate
 *                         logic)
 *
 *  @return A window object upon success, nil otherwise
 *
 *  @author Ayodeji Oshinnaiye, December 21, 2015
 */
-(NSWindow*)nextWindow: (NSWindow*)startingWindow
   withCyclicIteration: (BOOL)cyclicIteration
   withFilterPredicate: (NSPredicate*)filterPredicate;

@property (copy) NSString* productSpecificDisplayName;
@end

enum {
    NNAClickedOutsideModal = 3
};
