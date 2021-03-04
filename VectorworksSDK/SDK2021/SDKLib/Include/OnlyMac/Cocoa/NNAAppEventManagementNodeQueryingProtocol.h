//
//  NNAAppEventManagementNodeQueryingProtocol.h
//  VectorWorks
//
//  Created by Ayodeji Oshinnaiye on 2/14/20.
//

#pragma once

/*!
 * Protocol that defines a general interface for
 *  capabilities discovery on objects that may
 *  manage or directly interact with the host
 *  application event loop.
 *
 *  @author Ayodeji Oshinnaiye, February 14, 2020
 */
@protocol NNAAppEventManagementNodeQueryingProtocol

/*!
 * Determines if the receiving object implements
 *  an event loop that may interact with the
 *  application event loop, or supplant its
 *  functionality under certain conditions
 *
 * @return YES if the object implements a custom
 *         event loop
 *
 *  @author Ayodeji Oshinnaiye, February 14, 2020
 */
- (BOOL) implementsCustomEventLoop;

@end
