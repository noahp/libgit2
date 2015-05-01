/*
 * Copyright (C) the libgit2 contributors. All rights reserved.
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */
#ifndef INCLUDE_git_push_h__
#define INCLUDE_git_push_h__

#include "common.h"
#include "pack.h"

/**
 * @file git2/push.h
 * @brief Git push management functions
 * @defgroup git_push push management functions
 * @ingroup Git
 * @{
 */
GIT_BEGIN_DECL

/**
 * Controls the behavior of a git_push object.
 */
typedef struct {
	unsigned int version;

	/**
	 * If the transport being used to push to the remote requires the creation
	 * of a pack file, this controls the number of worker threads used by
	 * the packbuilder when creating that pack file to be sent to the remote.
	 *
	 * If set to 0, the packbuilder will auto-detect the number of threads
	 * to create. The default value is 1.
	 */
	unsigned int pb_parallelism;
} git_push_options;

#define GIT_PUSH_OPTIONS_VERSION 1
#define GIT_PUSH_OPTIONS_INIT { GIT_PUSH_OPTIONS_VERSION }

/**
 * Initializes a `git_push_options` with default values. Equivalent to
 * creating an instance with GIT_PUSH_OPTIONS_INIT.
 *
 * @param opts the `git_push_options` instance to initialize.
 * @param version the version of the struct; you should pass
 *        `GIT_PUSH_OPTIONS_VERSION` here.
 * @return Zero on success; -1 on failure.
 */
GIT_EXTERN(int) git_push_init_options(
	git_push_options *opts,
	unsigned int version);

/** Push network progress notification function */
typedef int (*git_push_transfer_progress)(
	unsigned int current,
	unsigned int total,
	size_t bytes,
	void* payload);

/**
 * Represents an update which will be performed on the remote during push
 */
typedef struct {
	/**
	 * The source name of the reference
	 */
	char *src_refname;
	/**
	 * The name of the reference to update on the server
	 */
	char *dst_refname;
	/**
	 * The current target of the reference
	 */
	git_oid src;
	/**
	 * The new target for the reference
	 */
	git_oid dst;
} git_push_update;

/**
 * @param updates an array containing the updates which will be sent
 * as commands to the destination.
 * @param len number of elements in `updates`
 * @param payload Payload provided by the caller
 */
typedef int (*git_push_negotiation)(const git_push_update **updates, size_t len, void *payload);

/** @} */
GIT_END_DECL
#endif
