//
//  ASDisplayNode+UIViewBridge.h
//  AsyncDisplayKit
//
//  Created by janezhuang on 2023/9/16.
//  Copyright © 2023 Facebook. All rights reserved.
//

#import <AsyncDisplayKit/ASDisplayNode.h>

/**
 * ## UIView bridge
 *
 * ASDisplayNode provides thread-safe access to most of UIView and CALayer properties and methods, traditionally unsafe.
 *
 * Using them will not cause the actual view/layer to be created, and will be applied when it is created (when the view
 * or layer property is accessed).
 *
 * After the view is created, the properties pass through to the view directly as if called on the main thread.
 *
 * @see UIView and CALayer for documentation on these common properties.
 */
@interface ASDisplayNode (UIViewBridge)

- (void)setNeedsDisplay; // Marks the view as needing display. Convenience for use whether view is created or not, or from a background thread.
- (void)setNeedsLayout; // Marks the view as needing layout.  Convenience for use whether view is created or not, or from a background thread.

@property (atomic, retain) id contents; // default=nil
@property (atomic, assign) BOOL clipsToBounds; // default==NO
@property (atomic, getter=isOpaque) BOOL opaque; // default==YES

@property (atomic, assign) BOOL allowsEdgeAntialiasing;
@property (atomic, assign) unsigned int edgeAntialiasingMask; // default==all values from CAEdgeAntialiasingMask

@property (atomic, getter=isHidden) BOOL hidden; // default==NO
@property (atomic, assign) BOOL needsDisplayOnBoundsChange; // default==NO
@property (atomic, assign) BOOL autoresizesSubviews; // default==YES (undefined for layer-backed nodes)
@property (atomic, assign) UIViewAutoresizing autoresizingMask; // default==UIViewAutoresizingNone  (undefined for layer-backed nodes)
@property (atomic, assign) CGFloat alpha; // default=1.0f
@property (atomic, assign) CGRect bounds; // default=CGRectZero
@property (atomic, assign) CGRect frame; // default=CGRectZero
@property (atomic, assign) CGPoint anchorPoint; // default={0.5, 0.5}
@property (atomic, assign) CGFloat zPosition; // default=0.0
@property (atomic, assign) CGPoint position; // default=CGPointZero
@property (atomic, assign) CGFloat contentsScale; // default=1.0f. See @contentsScaleForDisplay for more info
@property (atomic, assign) CATransform3D transform; // default=CATransform3DIdentity
@property (atomic, assign) CATransform3D subnodeTransform; // default=CATransform3DIdentity
@property (atomic, copy) NSString *name; // default=nil. Use this to tag your layers in the server-recurse-description / pca or for your own purposes

/**
 * @abstract The node view's background color.
 *
 * @discussion In contrast to UIView, setting a transparent color will not set opaque = NO.
 * This only affects nodes that implement +drawRect like ASTextNode.
*/
@property (atomic, retain) UIColor *backgroundColor; // default=nil

/**
 * @abstract A flag used to determine how a node lays out its content when its bounds change.
 *
 * @discussion This is like UIView's contentMode property, but better. We do our own mapping to layer.contentsGravity in
 * _ASDisplayView. You can set needsDisplayOnBoundsChange independently.
 * Thus, UIViewContentModeRedraw is not allowed; use needsDisplayOnBoundsChange = YES instead, and pick an appropriate
 * contentMode for your content while it's being re-rendered.
 */
@property (atomic, assign) UIViewContentMode contentMode; // default=UIViewContentModeScaleToFill

@property (atomic, assign, getter=isUserInteractionEnabled) BOOL userInteractionEnabled; // default=YES (NO for layer-backed nodes)
@property (atomic, assign, getter=isExclusiveTouch) BOOL exclusiveTouch; // default=NO
@property (atomic, assign) CGColorRef shadowColor; // default=opaque rgb black
@property (atomic, assign) CGFloat shadowOpacity; // default=0.0
@property (atomic, assign) CGSize shadowOffset; // default=(0, -3)
@property (atomic, assign) CGFloat shadowRadius; // default=3
@property (atomic, assign) CGFloat borderWidth; // default=0
@property (atomic, assign) CGColorRef borderColor; // default=opaque rgb black

// Accessibility support
@property (atomic, assign) BOOL isAccessibilityElement;
@property (atomic, copy) NSString *accessibilityLabel;
@property (atomic, copy) NSString *accessibilityHint;
@property (atomic, copy) NSString *accessibilityValue;
@property (atomic, assign) UIAccessibilityTraits accessibilityTraits;
@property (atomic, assign) CGRect accessibilityFrame;
@property (atomic, retain) NSString *accessibilityLanguage;
@property (atomic, assign) BOOL accessibilityElementsHidden;
@property (atomic, assign) BOOL accessibilityViewIsModal;
@property (atomic, assign) BOOL shouldGroupAccessibilityChildren;

@end
