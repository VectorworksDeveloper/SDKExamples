//
//  NNAVWHostApplicationProtocol.h
//  Vectorworks Executable
//
//  Created by Ayodeji Oshinnaiye on 1/11/18.
//

#pragma once

/*!
 *  Protocol that defines an interface to the application
 *   for functionality that should be explicitly provided
 *   to clients implemented as modular logic
 *   (e.g. plug-ins). Ideally, such clients
 *   should not access the internal application
 *   object interface, instead using only the
 *   methods exposed by protocol compliance.
 *
 *  @author Ayodeji Oshinnaiye, January 10, 2018
 */
@protocol NNAVWHostApplicationProtocol

@optional

/*!
 *  Requests that the application perform explicit key
 *   equivalent handling for a particular window - the
 *   window will not be provided with an opportunity to
 *   handle/interpret the key equivalent
 *
 *  @param targetWindow The window for which explicit key
 *                      equivalent handling will be performed
 *
 *  @author Ayodeji Oshinnaiye, January 10, 2018
 */
- (void)requestExplicitKeyEquivalentHandling: (NSWindow*) targetWindow;

@end
